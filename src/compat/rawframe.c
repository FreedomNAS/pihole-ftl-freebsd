/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Raw Ethernet frames through bpf(4), standing in for Linux's AF_PACKET
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#include "compat/rawframe.h"

#ifndef __linux__
#include <errno.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_types.h>

// A read() from bpf(4) returns every frame captured so far, each behind its
// own bpf_hdr. Frames not handed out yet wait here, one buffer per descriptor
// (each descriptor belongs to a single thread)
#define RAWFRAME_MAX_FDS 1024
static struct {
	unsigned char *buf;
	size_t size;
	size_t len;
	size_t off;
} pending[RAWFRAME_MAX_FDS];

int rawframe_open(const char *iface, const struct bpf_program *filter)
{
	const int fd = open("/dev/bpf", O_RDWR | O_CLOEXEC);
	if(fd < 0)
		return -1;
	if(fd >= RAWFRAME_MAX_FDS)
	{
		close(fd);
		errno = EMFILE;
		return -1;
	}

	u_int size = 0;
	struct ifreq ifr = { 0 };
	strncpy(ifr.ifr_name, iface, sizeof(ifr.ifr_name) - 1);
	if(ioctl(fd, BIOCGBLEN, &size) < 0 ||
	   ioctl(fd, BIOCSETIF, &ifr) < 0 ||
	   // Deliver frames as they arrive instead of when the buffer is full
	   ioctl(fd, BIOCIMMEDIATE, &(u_int){ 1 }) < 0 ||
	   // We write the source address of our frames ourselves
	   ioctl(fd, BIOCSHDRCMPLT, &(u_int){ 1 }) < 0 ||
	   // Only what arrives, not what we send
	   ioctl(fd, BIOCSDIRECTION, &(u_int){ BPF_D_IN }) < 0 ||
	   (filter != NULL && ioctl(fd, BIOCSETF, filter) < 0))
	{
		const int err = errno;
		close(fd);
		errno = err;
		return -1;
	}

	pending[fd].buf = malloc(size);
	if(pending[fd].buf == NULL)
	{
		close(fd);
		errno = ENOMEM;
		return -1;
	}
	pending[fd].size = size;
	pending[fd].len = pending[fd].off = 0;

	return fd;
}

ssize_t rawframe_send(const int fd, const void *frame, const size_t len)
{
	return write(fd, frame, len);
}

ssize_t rawframe_recv(const int fd, void *buf, const size_t len, const int timeout_ms)
{
	if(fd < 0 || fd >= RAWFRAME_MAX_FDS || pending[fd].buf == NULL)
	{
		errno = EBADF;
		return -1;
	}

	if(pending[fd].off >= pending[fd].len)
	{
		struct pollfd pfd = { .fd = fd, .events = POLLIN, .revents = 0 };
		const int ret = poll(&pfd, 1, timeout_ms);
		if(ret <= 0)
			return ret;

		const ssize_t got = read(fd, pending[fd].buf, pending[fd].size);
		if(got < 0)
			return -1;
		pending[fd].len = (size_t)got;
		pending[fd].off = 0;
		if(got == 0)
			return 0;
	}

	const struct bpf_hdr *hdr = (const struct bpf_hdr *)(pending[fd].buf + pending[fd].off);
	if(pending[fd].off + sizeof(*hdr) > pending[fd].len ||
	   pending[fd].off + hdr->bh_hdrlen + hdr->bh_caplen > pending[fd].len)
	{
		// Malformed buffer: drop what is left
		pending[fd].off = pending[fd].len;
		return 0;
	}

	const size_t caplen = hdr->bh_caplen;
	memcpy(buf, pending[fd].buf + pending[fd].off + hdr->bh_hdrlen, caplen < len ? caplen : len);
	pending[fd].off += BPF_WORDALIGN(hdr->bh_hdrlen + hdr->bh_caplen);

	return (ssize_t)caplen;
}

int rawframe_close(const int fd)
{
	if(fd >= 0 && fd < RAWFRAME_MAX_FDS)
	{
		free(pending[fd].buf);
		pending[fd].buf = NULL;
		pending[fd].size = pending[fd].len = pending[fd].off = 0;
	}
	return close(fd);
}

bool rawframe_hwaddr(const char *iface, unsigned char mac[ETH_ALEN])
{
	struct ifaddrs *addrs = NULL;
	if(getifaddrs(&addrs) != 0)
		return false;

	bool found = false;
	for(const struct ifaddrs *ifa = addrs; ifa != NULL; ifa = ifa->ifa_next)
	{
		if(ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_LINK ||
		   strcmp(ifa->ifa_name, iface) != 0)
			continue;

		const struct sockaddr_dl *sdl = (const struct sockaddr_dl *)ifa->ifa_addr;
		if(sdl->sdl_alen == ETH_ALEN)
		{
			memcpy(mac, LLADDR(sdl), ETH_ALEN);
			found = true;
		}
		break;
	}

	freeifaddrs(addrs);
	return found;
}
#endif // !__linux__
