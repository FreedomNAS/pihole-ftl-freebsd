/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Path of the running executable, like readlink("/proc/self/exe")
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef COMPAT_SELFEXE_H
#define COMPAT_SELFEXE_H

#include <sys/types.h>
#include <unistd.h>
#ifdef __FreeBSD__
#include <sys/sysctl.h>
#endif

// Same contract as readlink(): no terminating NUL, -1 and errno on failure
static inline ssize_t self_exe(char *buf, const size_t size)
{
#ifdef __FreeBSD__
	int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
	size_t len = size;
	if(sysctl(mib, 4, buf, &len, NULL, 0) != 0)
		return -1;
	// sysctl counts the terminating NUL
	return len > 0 ? (ssize_t)len - 1 : 0;
#else
	return readlink("/proc/self/exe", buf, size);
#endif
}

#endif // COMPAT_SELFEXE_H
