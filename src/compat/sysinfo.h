/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Linux sysinfo() on systems without <sys/sysinfo.h>
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef COMPAT_SYSINFO_H
#define COMPAT_SYSINFO_H

#ifdef __linux__
#include <sys/sysinfo.h>
#else

#define SI_LOAD_SHIFT 16

// The fields of Linux's struct sysinfo FTL reads, in the same units:
// seconds, loads scaled by 1 << SI_LOAD_SHIFT, memory in mem_unit bytes
struct sysinfo {
	long uptime;
	unsigned long loads[3];
	unsigned long totalram;
	unsigned long freeram;
	unsigned long sharedram;
	unsigned long bufferram;
	unsigned long totalswap;
	unsigned long freeswap;
	unsigned short procs;
	unsigned int mem_unit;
};

int sysinfo(struct sysinfo *info);
int get_nprocs_conf(void);
int get_nprocs(void);

#endif // __linux__
#endif // COMPAT_SYSINFO_H
