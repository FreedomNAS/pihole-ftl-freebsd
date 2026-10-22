/* Pi-hole: A black hole for Internet advertisements
*  (c) 2019 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Linux capabilities prototypes
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef CAPABILITIES_H
#define CAPABILITIES_H

#include <stdbool.h>
#ifdef __linux__
#include <linux/capability.h>
#else
// No per-process capabilities: the numbers only name what FTL asks for,
// capabilities.c maps each to the system setting that grants it
#define CAP_CHOWN            0
#define CAP_NET_BIND_SERVICE 10
#define CAP_NET_ADMIN        12
#define CAP_NET_RAW          13
#define CAP_IPC_LOCK         14
#define CAP_SYS_NICE         23
#define CAP_SYS_TIME         25
#endif

bool check_capability(const unsigned int cap);
bool check_capabilities(void);
bool suspend_capability(const unsigned int cap);
bool restore_capability_for_exec(const unsigned int cap);
bool use_capability(const unsigned int cap, const bool enable);

#endif //CAPABILITIES_H
