/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  prctl() thread naming on systems without <sys/prctl.h>
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef COMPAT_PRCTL_H
#define COMPAT_PRCTL_H

#include <pthread.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __FreeBSD__
#include <pthread_np.h>
#endif

#define PR_SET_NAME 15
#define PR_GET_NAME 16

// Only the two thread-naming options FTL uses; the Linux name length (16
// bytes including the terminator) is what callers expect from PR_GET_NAME
static inline int prctl(int option, ...)
{
	va_list ap;
	va_start(ap, option);
	char *name = va_arg(ap, char *);
	va_end(ap);

	switch(option)
	{
		case PR_SET_NAME:
			return pthread_setname_np(pthread_self(), name) == 0 ? 0 : -1;
		case PR_GET_NAME:
			if(pthread_getname_np(pthread_self(), name, 16) != 0)
				return -1;
			// Linux names a thread after its process until it is renamed
			if(name[0] == '\0')
				snprintf(name, 16, "%s", getprogname());
			return 0;
		default:
			errno = EINVAL;
			return -1;
	}
}

#endif // COMPAT_PRCTL_H
