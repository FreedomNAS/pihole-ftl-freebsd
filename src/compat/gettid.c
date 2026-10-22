/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  gettid() where libc declares it but does not provide it
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */

#if defined(__FreeBSD__)
#include <sys/types.h>
#include <pthread.h>
#include <pthread_np.h>
#include <unistd.h>

pid_t gettid(void)
{
	return (pid_t)pthread_getthreadid_np();
}
#endif
