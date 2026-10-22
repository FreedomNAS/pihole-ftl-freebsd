/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Linux sysinfo() from sysctl(3)
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#include "compat/sysinfo.h"

#ifndef __linux__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/user.h>
#include <vm/vm_param.h>

int sysinfo(struct sysinfo *info)
{
	memset(info, 0, sizeof(*info));
	info->mem_unit = 1;

	struct timeval boottime;
	size_t len = sizeof(boottime);
	if(sysctlbyname("kern.boottime", &boottime, &len, NULL, 0) != 0)
		return -1;
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	info->uptime = now.tv_sec - boottime.tv_sec;

	struct loadavg la;
	len = sizeof(la);
	if(sysctlbyname("vm.loadavg", &la, &len, NULL, 0) == 0 && la.fscale > 0)
		for(unsigned int i = 0; i < 3; i++)
			info->loads[i] = (unsigned long)(((double)la.ldavg[i] / la.fscale) * (1 << SI_LOAD_SHIFT));

	unsigned long physmem = 0;
	len = sizeof(physmem);
	if(sysctlbyname("hw.physmem", &physmem, &len, NULL, 0) == 0)
		info->totalram = physmem;
	unsigned int free_pages = 0;
	len = sizeof(free_pages);
	if(sysctlbyname("vm.stats.vm.v_free_count", &free_pages, &len, NULL, 0) == 0)
		info->freeram = (unsigned long)free_pages * (unsigned long)getpagesize();

	// vm.swap_info.N holds one struct xswdev per swap device
	int mib[3];
	size_t miblen = 2;
	if(sysctlnametomib("vm.swap_info", mib, &miblen) == 0)
	{
		for(int n = 0; ; n++)
		{
			struct xswdev xsw;
			len = sizeof(xsw);
			mib[2] = n;
			if(sysctl(mib, 3, &xsw, &len, NULL, 0) != 0)
				break;
			info->totalswap += (unsigned long)xsw.xsw_nblks * getpagesize();
			info->freeswap += (unsigned long)(xsw.xsw_nblks - xsw.xsw_used) * getpagesize();
		}
	}

	int procs = 0;
	len = 0;
	int pmib[3] = { CTL_KERN, KERN_PROC, KERN_PROC_PROC };
	if(sysctl(pmib, 3, NULL, &len, NULL, 0) == 0)
		procs = (int)(len / sizeof(struct kinfo_proc));
	info->procs = (unsigned short)procs;

	return 0;
}

int get_nprocs_conf(void)
{
	return (int)sysconf(_SC_NPROCESSORS_CONF);
}

int get_nprocs(void)
{
	return (int)sysconf(_SC_NPROCESSORS_ONLN);
}
#endif // __linux__
