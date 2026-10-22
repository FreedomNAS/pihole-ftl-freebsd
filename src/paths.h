/* Pi-hole: A black hole for Internet advertisements
*  (c) 2026 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Installation directories
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */
#ifndef PATHS_H
#define PATHS_H

// The build sets these (src/CMakeLists.txt) from the platform's file system
// layout; the fallbacks are the Linux one

// Configuration, databases and the files FTL writes beside them
#ifndef PIHOLE_CONFDIR
#define PIHOLE_CONFDIR "/etc/pihole"
#endif

// Log files
#ifndef PIHOLE_LOGDIR
#define PIHOLE_LOGDIR "/var/log/pihole"
#endif

// Document root of the web interface
#ifndef PIHOLE_WEBROOT
#define PIHOLE_WEBROOT "/var/www/html"
#endif

// Additional dnsmasq configuration (misc.etc_dnsmasq_d)
#ifndef DNSMASQ_D_DIR
#define DNSMASQ_D_DIR "/etc/dnsmasq.d"
#endif

#endif // PATHS_H
