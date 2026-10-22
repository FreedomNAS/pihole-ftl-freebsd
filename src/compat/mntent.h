/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  struct mntent on systems without <mntent.h>
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef COMPAT_MNTENT_H
#define COMPAT_MNTENT_H

#ifdef __linux__
#include <mntent.h>
#else
struct mntent {
	char *mnt_fsname;
	char *mnt_dir;
	char *mnt_type;
	char *mnt_opts;
	int mnt_freq;
	int mnt_passno;
};
#endif

#endif // COMPAT_MNTENT_H
