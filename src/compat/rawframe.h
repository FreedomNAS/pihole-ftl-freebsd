/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Raw Ethernet frames through bpf(4), standing in for Linux's AF_PACKET
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef COMPAT_RAWFRAME_H
#define COMPAT_RAWFRAME_H

#ifndef __linux__
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <net/bpf.h>

// Linux names for the Ethernet header, used by the tools that build frames
#define ETH_ALEN 6
#define ETH_HLEN 14
#define ETH_P_IP 0x0800
#define ETH_P_ARP 0x0806

struct ethhdr {
	unsigned char h_dest[ETH_ALEN];
	unsigned char h_source[ETH_ALEN];
	uint16_t h_proto;
} __attribute__((packed));

// Opens a bpf(4) device on iface that receives the frames the filter
// accepts (all frames when filter is NULL) and sends complete frames,
// including our own Ethernet header. Returns the descriptor or -1 with errno
int rawframe_open(const char *iface, const struct bpf_program *filter);

// Sends one complete frame
ssize_t rawframe_send(const int fd, const void *frame, const size_t len);

// Copies the next frame received into buf (truncated to len) and returns its
// length, 0 when nothing arrived within timeout_ms, -1 with errno on errors
ssize_t rawframe_recv(const int fd, void *buf, const size_t len, const int timeout_ms);

int rawframe_close(const int fd);

// MAC address of iface, false if there is none
bool rawframe_hwaddr(const char *iface, unsigned char mac[ETH_ALEN]);
#endif // !__linux__

#endif // COMPAT_RAWFRAME_H
