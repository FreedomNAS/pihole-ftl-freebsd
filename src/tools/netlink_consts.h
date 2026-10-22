/* Pi-hole: A black hole for Internet advertisements
*  (c) 2024 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Netlink constants
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */

#include "netlink.h"

#ifdef __linux__
static struct flag_names iflatypes[] =
{
#if defined(__linux__) || defined(ARPHRD_NETROM)
	{ ARPHRD_NETROM, "netrom" },
#endif
	{ ARPHRD_ETHER, "ether" },
#if defined(__linux__) || defined(ARPHRD_EETHER)
	{ ARPHRD_EETHER, "eether" },
#endif
#if defined(__linux__) || defined(ARPHRD_AX25)
	{ ARPHRD_AX25, "ax25" },
#endif
#if defined(__linux__) || defined(ARPHRD_PRONET)
	{ ARPHRD_PRONET, "pronet" },
#endif
#if defined(__linux__) || defined(ARPHRD_CHAOS)
	{ ARPHRD_CHAOS, "chaos" },
#endif
	{ ARPHRD_IEEE802, "ieee802" },
#if defined(__linux__) || defined(ARPHRD_ARCNET)
	{ ARPHRD_ARCNET, "arcnet" },
#endif
#if defined(__linux__) || defined(ARPHRD_APPLETLK)
	{ ARPHRD_APPLETLK, "appletlk" },
#endif
#if defined(__linux__) || defined(ARPHRD_DLCI)
	{ ARPHRD_DLCI, "dlci" },
#endif
#if defined(__linux__) || defined(ARPHRD_ATM)
	{ ARPHRD_ATM, "atm" },
#endif
#if defined(__linux__) || defined(ARPHRD_METRICOM)
	{ ARPHRD_METRICOM, "metricom" },
#endif
	{ ARPHRD_IEEE1394, "ieee1394" },
#if defined(__linux__) || defined(ARPHRD_EUI64)
	{ ARPHRD_EUI64, "eui64" },
#endif
	{ ARPHRD_INFINIBAND, "infiniband" },
#if defined(__linux__) || defined(ARPHRD_SLIP)
	{ ARPHRD_SLIP, "slip" },
#endif
#if defined(__linux__) || defined(ARPHRD_CSLIP)
	{ ARPHRD_CSLIP, "cslip" },
#endif
#if defined(__linux__) || defined(ARPHRD_SLIP6)
	{ ARPHRD_SLIP6, "slip6" },
#endif
#if defined(__linux__) || defined(ARPHRD_CSLIP6)
	{ ARPHRD_CSLIP6, "cslip6" },
#endif
#if defined(__linux__) || defined(ARPHRD_RSRVD)
	{ ARPHRD_RSRVD, "rsrvd" },
#endif
#if defined(__linux__) || defined(ARPHRD_ADAPT)
	{ ARPHRD_ADAPT, "adapt" },
#endif
#if defined(__linux__) || defined(ARPHRD_ROSE)
	{ ARPHRD_ROSE, "rose" },
#endif
#if defined(__linux__) || defined(ARPHRD_X25)
	{ ARPHRD_X25, "x25" },
#endif
#if defined(__linux__) || defined(ARPHRD_HWX25)
	{ ARPHRD_HWX25, "hwx25" },
#endif
#if defined(__linux__) || defined(ARPHRD_CAN)
	{ ARPHRD_CAN, "can" },
#endif
#if defined (ARPHRD_MCTP)
	// 2025-May: kernel version dependent
	{ ARPHRD_MCTP, "mctp" },
#endif
#if defined(__linux__) || defined(ARPHRD_PPP)
	{ ARPHRD_PPP, "ppp" },
#endif
#if defined(__linux__) || defined(ARPHRD_CISCO)
	{ ARPHRD_CISCO, "cisco" },
#endif
#if defined(__linux__) || defined(ARPHRD_HDLC)
	{ ARPHRD_HDLC, "hdlc" },
#endif
#if defined(__linux__) || defined(ARPHRD_CISCO)
	{ ARPHRD_CISCO, "cisco" },
#endif
#if defined(__linux__) || defined(ARPHRD_LAPB)
	{ ARPHRD_LAPB, "lapb" },
#endif
#if defined(__linux__) || defined(ARPHRD_DDCMP)
	{ ARPHRD_DDCMP, "ddcmp" },
#endif
#if defined(__linux__) || defined(ARPHRD_RAWHDLC)
	{ ARPHRD_RAWHDLC, "rawhdlc" },
#endif
#if defined(__linux__) || defined(ARPHRD_RAWIP)
	{ ARPHRD_RAWIP, "rawip" },
#endif
#if defined(__linux__) || defined(ARPHRD_TUNNEL)
	{ ARPHRD_TUNNEL, "tunnel" },
#endif
#if defined(__linux__) || defined(ARPHRD_TUNNEL6)
	{ ARPHRD_TUNNEL6, "tunnel6" },
#endif
#if defined(__linux__) || defined(ARPHRD_FRAD)
	{ ARPHRD_FRAD, "frad" },
#endif
#if defined(__linux__) || defined(ARPHRD_SKIP)
	{ ARPHRD_SKIP, "skip" },
#endif
#if defined(__linux__) || defined(ARPHRD_LOOPBACK)
	{ ARPHRD_LOOPBACK, "loopback" },
#endif
#if defined(__linux__) || defined(ARPHRD_LOCALTLK)
	{ ARPHRD_LOCALTLK, "localtlk" },
#endif
#if defined(__linux__) || defined(ARPHRD_FDDI)
	{ ARPHRD_FDDI, "fddi" },
#endif
#if defined(__linux__) || defined(ARPHRD_BIF)
	{ ARPHRD_BIF, "bif" },
#endif
#if defined(__linux__) || defined(ARPHRD_SIT)
	{ ARPHRD_SIT, "sit" },
#endif
#if defined(__linux__) || defined(ARPHRD_IPDDP)
	{ ARPHRD_IPDDP, "ipddp" },
#endif
#if defined(__linux__) || defined(ARPHRD_IPGRE)
	{ ARPHRD_IPGRE, "ipgre" },
#endif
#if defined(__linux__) || defined(ARPHRD_PIMREG)
	{ ARPHRD_PIMREG, "pimreg" },
#endif
#if defined(__linux__) || defined(ARPHRD_HIPPI)
	{ ARPHRD_HIPPI, "hippi" },
#endif
#if defined(__linux__) || defined(ARPHRD_ASH)
	{ ARPHRD_ASH, "ash" },
#endif
#if defined(__linux__) || defined(ARPHRD_ECONET)
	{ ARPHRD_ECONET, "econet" },
#endif
#if defined(__linux__) || defined(ARPHRD_IRDA)
	{ ARPHRD_IRDA, "irda" },
#endif
#if defined(__linux__) || defined(ARPHRD_FCPP)
	{ ARPHRD_FCPP, "fcpp" },
#endif
#if defined(__linux__) || defined(ARPHRD_FCAL)
	{ ARPHRD_FCAL, "fcal" },
#endif
#if defined(__linux__) || defined(ARPHRD_FCPL)
	{ ARPHRD_FCPL, "fcpl" },
#endif
#if defined(__linux__) || defined(ARPHRD_FCFABRIC)
	{ ARPHRD_FCFABRIC, "fcfabric" },
#endif
#if defined(__linux__) || defined(ARPHRD_IEEE802_TR)
	{ ARPHRD_IEEE802_TR, "ieee802_tr" },
#endif
#if defined(__linux__) || defined(ARPHRD_IEEE80211)
	{ ARPHRD_IEEE80211, "ieee80211" },
#endif
#if defined(__linux__) || defined(ARPHRD_IEEE80211_PRISM)
	{ ARPHRD_IEEE80211_PRISM, "ieee80211_prism" },
#endif
#if defined(__linux__) || defined(ARPHRD_IEEE80211_RADIOTAP)
	{ ARPHRD_IEEE80211_RADIOTAP, "ieee80211_radiotap" },
#endif
#if defined(__linux__) || defined(ARPHRD_IEEE802154)
	{ ARPHRD_IEEE802154, "ieee802154" },
#endif
#if defined(__linux__) || defined(ARPHRD_IEEE802154_MONITOR)
	{ ARPHRD_IEEE802154_MONITOR, "ieee802154_monitor" },
#endif
#if defined(__linux__) || defined(ARPHRD_PHONET)
	{ ARPHRD_PHONET, "phonet" },
#endif
#if defined(__linux__) || defined(ARPHRD_PHONET_PIPE)
	{ ARPHRD_PHONET_PIPE, "phonet_pipe" },
#endif
#if defined(__linux__) || defined(ARPHRD_CAIF)
	{ ARPHRD_CAIF, "caif" },
#endif
#if defined(__linux__) || defined(ARPHRD_IP6GRE)
	{ ARPHRD_IP6GRE, "ip6gre" },
#endif
#if defined(__linux__) || defined(ARPHRD_NETLINK)
	{ ARPHRD_NETLINK, "netlink" },
#endif
#if defined(__linux__) || defined(ARPHRD_6LOWPAN)
	{ ARPHRD_6LOWPAN, "6lowpan" },
#endif
#if defined(__linux__) || defined(ARPHRD_VSOCKMON)
	{ ARPHRD_VSOCKMON, "vsockmon" },
#endif
#if defined(__linux__) || defined(ARPHRD_VOID)
	{ ARPHRD_VOID, "void" },
#endif
#if defined(__linux__) || defined(ARPHRD_NONE)
	{ ARPHRD_NONE, "none" },
#endif
};
#else
// FreeBSD reports its own interface types (IFT_*) in ifi_type
#include <net/if_types.h>
static struct flag_names iflatypes[] =
{
	{ IFT_ETHER, "ether" },
	{ IFT_LOOP, "loopback" },
	{ IFT_BRIDGE, "bridge" },
	{ IFT_L2VLAN, "vlan" },
	{ IFT_IEEE8023ADLAG, "lagg" },
	{ IFT_IEEE80211, "ieee80211" },
	{ IFT_INFINIBAND, "infiniband" },
	{ IFT_TUNNEL, "tunnel" },
	{ IFT_GIF, "gif" },
	{ IFT_STF, "stf" },
	{ IFT_PPP, "ppp" },
	{ IFT_PROPVIRTUAL, "virtual" },
	{ IFT_PFLOG, "pflog" },
	{ IFT_PFSYNC, "pfsync" },
	{ IFT_ENC, "enc" },
};
#endif

static struct flag_names ifaf_flags[] = {
	{ IFA_F_SECONDARY, "secondary" },
	{ IFA_F_TEMPORARY, "temporary" },
	{ IFA_F_NODAD, "nodad" },
	{ IFA_F_OPTIMISTIC, "optimistic" },
	{ IFA_F_DADFAILED, "dadfailed" },
	{ IFA_F_HOMEADDRESS, "homeaddress" },
	{ IFA_F_DEPRECATED, "deprecated" },
	{ IFA_F_TENTATIVE, "tentative" },
	{ IFA_F_PERMANENT, "permanent" },
	{ IFA_F_MANAGETEMPADDR, "managetempaddr" },
	{ IFA_F_NOPREFIXROUTE, "noprefixroute" },
	{ IFA_F_MCAUTOJOIN, "mcautojoin" },
	{ IFA_F_STABLE_PRIVACY, "stable_privacy" },
};

static struct flag_names iff_flags[] = {
	{ IFF_UP, "up" },
	{ IFF_BROADCAST, "broadcast" },
	{ IFF_DEBUG, "debug" },
	{ IFF_LOOPBACK, "loopback" },
	{ IFF_POINTOPOINT, "pointopoint" },
#if defined(__linux__) || defined(IFF_NOTRAILERS)
	{ IFF_NOTRAILERS, "notrailers" },
#endif
	{ IFF_RUNNING, "running" },
	{ IFF_NOARP, "noarp" },
	{ IFF_PROMISC, "promisc" },
	{ IFF_ALLMULTI, "allmulti" },
#if defined(__linux__) || defined(IFF_MASTER)
	{ IFF_MASTER, "master" },
#endif
#if defined(__linux__) || defined(IFF_SLAVE)
	{ IFF_SLAVE, "slave" },
#endif
	{ IFF_MULTICAST, "multicast" },
#if defined(__linux__) || defined(IFF_PORTSEL)
	{ IFF_PORTSEL, "portsel" },
#endif
#if defined(__linux__) || defined(IFF_AUTOMEDIA)
	{ IFF_AUTOMEDIA, "automedia" },
#endif
#if defined(__linux__) || defined(IFF_DYNAMIC)
	{ IFF_DYNAMIC, "dynamic" },
#endif
#ifdef IFF_LOWER_UP
	{ IFF_LOWER_UP, "lower_up" },
#endif
#ifdef IFF_DORMANT
	{ IFF_DORMANT, "dormant" },
#endif
#ifdef IFF_ECHO
	{ IFF_ECHO, "echo" },
#endif
};

static struct flag_names rtprots[] = {
	{ RTPROT_UNSPEC, "unspec" },
	{ RTPROT_REDIRECT, "redirect" },
	{ RTPROT_KERNEL, "kernel" },
	{ RTPROT_BOOT, "boot" },
	{ RTPROT_STATIC, "static" },
	{ RTPROT_GATED, "gated" },
	{ RTPROT_RA, "ra" },
	{ RTPROT_MRT, "mrt" },
	{ RTPROT_ZEBRA, "zebra" },
	{ RTPROT_BIRD, "bird" },
	{ RTPROT_DNROUTED, "dnrouted" },
	{ RTPROT_XORP, "xorp" },
	{ RTPROT_NTK, "ntk" },
	{ RTPROT_DHCP, "dhcp" },
	{ RTPROT_MROUTED, "mrouted" },
	{ RTPROT_KEEPALIVED, "keepalived" },
	{ RTPROT_BABEL, "babel" },
#if defined (RTPROT_OPENR)
	// 2025-May: kernel version dependent
	{ RTPROT_OPENR, "openr" },
#endif
	{ RTPROT_BGP, "bgp" },
	{ RTPROT_ISIS, "isis" },
	{ RTPROT_OSPF, "ospf" },
	{ RTPROT_RIP, "rip" },
	{ RTPROT_EIGRP, "eigrp" },
};

static struct flag_names rtscopes[] = {
	{ RT_SCOPE_UNIVERSE, "universe" },
	{ RT_SCOPE_SITE, "site" },
	{ RT_SCOPE_LINK, "link" },
	{ RT_SCOPE_HOST, "host" },
	{ RT_SCOPE_NOWHERE, "nowhere" },
};

static struct flag_names rttypes[] = {
	{ RTN_UNSPEC, "unspec" },
	{ RTN_UNICAST, "unicast" },
	{ RTN_LOCAL, "local" },
	{ RTN_BROADCAST, "broadcast" },
	{ RTN_ANYCAST, "anycast" },
	{ RTN_MULTICAST, "multicast" },
	{ RTN_BLACKHOLE, "blackhole" },
	{ RTN_UNREACHABLE, "unreachable" },
	{ RTN_PROHIBIT, "prohibit" },
	{ RTN_THROW, "throw" },
	{ RTN_NAT, "nat" },
	{ RTN_XRESOLVE, "xresolve" },
};

static struct flag_names rtmflags[] = {
	{ RTM_F_NOTIFY, "notify" },
	{ RTM_F_CLONED, "cloned" },
	{ RTM_F_EQUALIZE, "equalize" },
	{ RTM_F_PREFIX, "prefix" },
	{ RTM_F_LOOKUP_TABLE, "lookup_table" },
	{ RTM_F_FIB_MATCH, "fib_match" },
	{ RTM_F_OFFLOAD, "offload" },
	{ RTM_F_TRAP, "trap" },
#if defined (RTM_F_OFFLOAD_FAILED)
	// 2025-May: kernel version dependent
	{ RTM_F_OFFLOAD_FAILED, "offload_failed" },
#endif
};

static struct flag_names rtnhflags[] = {
	{ RTNH_F_DEAD, "dead" },
	{ RTNH_F_PERVASIVE, "pervasive" },
	{ RTNH_F_ONLINK, "onlink" },
	{ RTNH_F_OFFLOAD, "offload" },
	{ RTNH_F_LINKDOWN, "linkdown" },
	{ RTNH_F_UNRESOLVED, "unresolved" },
#if defined (RTNH_F_TRAP)
	// 2025-May: kernel version dependent
	{ RTNH_F_TRAP, "trap" },
#endif
};

static struct flag_names ifstates[] = {
	{ IF_OPER_UNKNOWN, "unknown" },
	{ IF_OPER_NOTPRESENT, "notpresent" },
	{ IF_OPER_DOWN, "down" },
	{ IF_OPER_LOWERLAYERDOWN, "lower_layer_down" },
	{ IF_OPER_TESTING, "testing" },
	{ IF_OPER_DORMANT, "dormant" },
	{ IF_OPER_UP, "up" },
};

#ifdef __linux__
static struct flag_names link_events[] = {
#if defined(__linux__) || defined(IFLA_EVENT_NONE)
	{ IFLA_EVENT_NONE, "none" },
#endif
#if defined(__linux__) || defined(IFLA_EVENT_REBOOT)
	{ IFLA_EVENT_REBOOT, "reboot" },
#endif
#if defined(__linux__) || defined(IFLA_EVENT_FEATURES)
	{ IFLA_EVENT_FEATURES, "feature change" },
#endif
#if defined(__linux__) || defined(IFLA_EVENT_BONDING_FAILOVER)
	{ IFLA_EVENT_BONDING_FAILOVER, "bonding failover" },
#endif
#if defined(__linux__) || defined(IFLA_EVENT_NOTIFY_PEERS)
	{ IFLA_EVENT_NOTIFY_PEERS, "notify peers" },
#endif
#if defined(__linux__) || defined(IFLA_EVENT_IGMP_RESEND)
	{ IFLA_EVENT_IGMP_RESEND, "resend igmp" },
#endif
#if defined(__linux__) || defined(IFLA_EVENT_BONDING_OPTIONS)
	{ IFLA_EVENT_BONDING_OPTIONS, "bonding option" },
#endif
};
#endif

#ifdef __linux__
static struct flag_names addr_gen_modes[] = {
#if defined(__linux__) || defined(IN6_ADDR_GEN_MODE_EUI64)
	{ IN6_ADDR_GEN_MODE_EUI64, "eui64" },
#endif
#if defined(__linux__) || defined(IN6_ADDR_GEN_MODE_NONE)
	{ IN6_ADDR_GEN_MODE_NONE, "none" },
#endif
#if defined(__linux__) || defined(IN6_ADDR_GEN_MODE_STABLE_PRIVACY)
	{ IN6_ADDR_GEN_MODE_STABLE_PRIVACY, "stable_secret" },
#endif
#if defined(__linux__) || defined(IN6_ADDR_GEN_MODE_RANDOM)
	{ IN6_ADDR_GEN_MODE_RANDOM, "random" },
#endif
};
#endif

static const char *__attribute__ ((const)) rtaTypeToString(const int rta_type)
{
	switch (rta_type) {
		case RTA_UNSPEC:
			return "unspec";
		case RTA_DST:
			return "dst";
		case RTA_SRC:
			return "src";
		case RTA_IIF:
			return "iif";
		case RTA_OIF:
			return "oif";
		case RTA_GATEWAY:
			return "gateway";
		case RTA_PRIORITY:
			return "priority";
		case RTA_PREFSRC:
			return "prefsrc";
		case RTA_METRICS:
			return "metrics";
		case RTA_MULTIPATH:
			return "multipath";
		case RTA_PROTOINFO:
			return "protoinfo";
		case RTA_FLOW:
			return "flow";
		case RTA_CACHEINFO:
			return "cacheinfo";
		case RTA_SESSION:
			return "session";
		case RTA_MP_ALGO:
			return "mp_algo";
		case RTA_TABLE:
			return "table";
		case RTA_MARK:
			return "mark";
		case RTA_MFC_STATS:
			return "mfc_stats";
		case RTA_VIA:
			return "via";
		case RTA_NEWDST:
			return "newdst";
		case RTA_PREF:
			return "pref";
		case RTA_ENCAP_TYPE:
			return "encap_type";
		case RTA_ENCAP:
			return "encap";
		case RTA_EXPIRES:
			return "expires";
		case RTA_PAD:
			return "pad";
		case RTA_UID:
			return "uid";
		case RTA_TTL_PROPAGATE:
			return "ttl_propagate";
		case RTA_IP_PROTO:
			return "ip_proto";
		case RTA_SPORT:
			return "sport";
		case RTA_DPORT:
			return "dport";
		case RTA_NH_ID:
			return "nh_id";
		default:
			return "unknown";
	}
}

static const char *__attribute__ ((const)) ifaTypeToString(const int ifa_type)
{
	switch (ifa_type) {
		case IFA_ADDRESS:
			return "address";
		case IFA_LOCAL:
			return "local";
		case IFA_LABEL:
			return "label";
		case IFA_BROADCAST:
			return "broadcast";
		case IFA_ANYCAST:
			return "anycast";
		case IFA_CACHEINFO:
			return "cacheinfo";
		case IFA_MULTICAST:
			return "multicast";
		case IFA_FLAGS:
			return "flags";
		case IFA_RT_PRIORITY:
			return "rt_priority";
		case IFA_TARGET_NETNSID:
			return "target_netnsid";
		default:
			return "unknown";
	}
}

static const char *__attribute__ ((const)) iflaTypeToString(const int ifla_type)
{
	switch (ifla_type)
	{
		case IFLA_UNSPEC:
			return "unspec";
		case IFLA_ADDRESS:
			return "address";
		case IFLA_BROADCAST:
			return "broadcast";
		case IFLA_IFNAME:
			return "ifname";
		case IFLA_MTU:
			return "mtu";
		case IFLA_LINK:
			return "link";
		case IFLA_QDISC:
			return "qdisc";
		case IFLA_STATS:
			return "stats";
		case IFLA_COST:
			return "cost";
		case IFLA_PRIORITY:
			return "priority";
		case IFLA_MASTER:
			return "master";
		case IFLA_WIRELESS:
			return "wireless";
		case IFLA_PROTINFO:
			return "protinfo";
		case IFLA_TXQLEN:
			return "txqlen";
		case IFLA_MAP:
			return "map";
		case IFLA_WEIGHT:
			return "weight";
		case IFLA_OPERSTATE:
			return "operstate";
		case IFLA_LINKMODE:
			return "linkmode";
		case IFLA_LINKINFO:
			return "linkinfo";
		case IFLA_NET_NS_FD:
			return "net_ns_fd";
		case IFLA_IFALIAS:
			return "ifalias";
		case IFLA_NUM_VF:
			return "num_vf";
		case IFLA_VFINFO_LIST:
			return "vfinfo_list";
		case IFLA_STATS64:
			return "stats64";
		case IFLA_VF_PORTS:
			return "vf_ports";
		case IFLA_PORT_SELF:
			return "port_self";
		case IFLA_AF_SPEC:
			return "af_spec";
		case IFLA_GROUP:
			return "group";
		case IFLA_NET_NS_PID:
			return "net_ns_pid";
		case IFLA_EXT_MASK:
			return "ext_mask";
		case IFLA_PROMISCUITY:
			return "promiscuity";
		case IFLA_NUM_TX_QUEUES:
			return "num_tx_queues";
		case IFLA_NUM_RX_QUEUES:
			return "num_rx_queues";
		case IFLA_CARRIER:
			return "carrier";
		case IFLA_PHYS_PORT_ID:
			return "phys_port_id";
		case IFLA_CARRIER_CHANGES:
			return "carrier_changes";
		case IFLA_PHYS_SWITCH_ID:
			return "phys_switch_id";
		case IFLA_LINK_NETNSID:
			return "link_netnsid";
		case IFLA_PHYS_PORT_NAME:
			return "phys_port_name";
		case IFLA_PROTO_DOWN:
			return "proto_down";
		case IFLA_GSO_MAX_SEGS:
			return "gso_max_segs";
		case IFLA_GSO_MAX_SIZE:
			return "gso_max_size";
		case IFLA_PAD:
			return "pad";
		case IFLA_XDP:
			return "xdp";
		case IFLA_EVENT:
			return "event";
		case IFLA_NEW_NETNSID:
			return "new_netnsid";
		case IFLA_IF_NETNSID:
			return "if_netnsid";
		case IFLA_CARRIER_UP_COUNT:
			return "carrier_up_count";
		case IFLA_CARRIER_DOWN_COUNT:
			return "carrier_down_count";
		case IFLA_NEW_IFINDEX:
			return "new_ifindex";
		case IFLA_MIN_MTU:
			return "min_mtu";
		case IFLA_MAX_MTU:
			return "max_mtu";
		case IFLA_PROP_LIST:
			return "prop_list";
		case IFLA_ALT_IFNAME:
			return "alt_ifname";
		case IFLA_PERM_ADDRESS:
			return "perm_address";
		case IFLA_PROTO_DOWN_REASON:
			return "proto_down_reason";
#if defined (IFLA_PARENT_DEV_NAME)
		// 2025-May: kernel version dependent
		case IFLA_PARENT_DEV_NAME:
			return "parent_dev_name";
#endif
#if defined (IFLA_PARENT_DEV_BUS_NAME)
		// 2025-May: kernel version dependent
		case IFLA_PARENT_DEV_BUS_NAME:
			return "parent_dev_bus_name";
#endif
		default:
			return "unknown";
	}
}

// Names of the RTAX_* attributes nested in RTA_METRICS (as used by iproute2)
static const char *__attribute__ ((const)) rtaxTypeToString(const int rtax_type)
{
	switch (rtax_type) {
		case RTAX_LOCK:
			return "lock";
		case RTAX_MTU:
			return "mtu";
		case RTAX_WINDOW:
			return "window";
		case RTAX_RTT:
			return "rtt";
		case RTAX_RTTVAR:
			return "rttvar";
		case RTAX_SSTHRESH:
			return "ssthresh";
		case RTAX_CWND:
			return "cwnd";
		case RTAX_ADVMSS:
			return "advmss";
		case RTAX_REORDERING:
			return "reordering";
		case RTAX_HOPLIMIT:
			return "hoplimit";
		case RTAX_INITCWND:
			return "initcwnd";
		case RTAX_FEATURES:
			return "features";
		case RTAX_RTO_MIN:
			return "rto_min";
		case RTAX_INITRWND:
			return "initrwnd";
		case RTAX_QUICKACK:
			return "quickack";
		case RTAX_CC_ALGO:
			return "congctl";
		case RTAX_FASTOPEN_NO_COOKIE:
			return "fastopen_no_cookie";
		default:
			return "unknown";
	}
}

static const char *__attribute__ ((const)) family_name(int family)
{
	switch(family)
	{
		case PF_UNSPEC:
			return "unspec";
		case PF_LOCAL:
			return "local";
		case PF_INET:
			return "inet";
#if defined(__linux__) || defined(PF_AX25)
		case PF_AX25:
			return "ax25";
#endif
		case PF_IPX:
			return "ipx";
		case PF_APPLETALK:
			return "appletalk";
#if defined(__linux__) || defined(PF_NETROM)
		case PF_NETROM:
			return "netrom";
#endif
#if defined(__linux__) || defined(PF_BRIDGE)
		case PF_BRIDGE:
			return "bridge";
#endif
#if defined(__linux__) || defined(PF_ATMPVC)
		case PF_ATMPVC:
			return "atmpvc";
#endif
#if defined(__linux__) || defined(PF_X25)
		case PF_X25:
			return "x25";
#endif
		case PF_INET6:
			return "inet6";
#if defined(__linux__) || defined(PF_ROSE)
		case PF_ROSE:
			return "rose";
#endif
		case PF_DECnet:
			return "decnet";
#if defined(__linux__) || defined(PF_NETBEUI)
		case PF_NETBEUI:
			return "netbeui";
#endif
#if defined(__linux__) || defined(PF_SECURITY)
		case PF_SECURITY:
			return "security";
#endif
		case PF_KEY:
			return "key";
		case PF_NETLINK:
			return "netlink";
#if defined(__linux__) || defined(PF_PACKET)
		case PF_PACKET:
			return "packet";
#endif
#if defined(__linux__) || defined(PF_ASH)
		case PF_ASH:
			return "ash";
#endif
#if defined(__linux__) || defined(PF_ECONET)
		case PF_ECONET:
			return "econet";
#endif
#if defined(__linux__) || defined(PF_ATMSVC)
		case PF_ATMSVC:
			return "atmsvc";
#endif
#if defined(__linux__) || defined(PF_RDS)
		case PF_RDS:
			return "rds";
#endif
		case PF_SNA:
			return "sna";
#if defined(__linux__) || defined(PF_IRDA)
		case PF_IRDA:
			return "irda";
#endif
#if defined(__linux__) || defined(PF_PPPOX)
		case PF_PPPOX:
			return "pppox";
#endif
#if defined(__linux__) || defined(PF_WANPIPE)
		case PF_WANPIPE:
			return "wanpipe";
#endif
#if defined(__linux__) || defined(PF_LLC)
		case PF_LLC:
			return "llc";
#endif
#if defined (PF_IB)
		// 2025-May: defined by glibc but not uClibc
		case PF_IB:
			return "ib";
#endif
#if defined (PF_MPLS)
		// 2025-May: defined by glibc but not uClibc
		case PF_MPLS:
			return "mpls";
#endif
#if defined(__linux__) || defined(PF_CAN)
		case PF_CAN:
			return "can";
#endif
#if defined(__linux__) || defined(PF_TIPC)
		case PF_TIPC:
			return "tipc";
#endif
		case PF_BLUETOOTH:
			return "bluetooth";
#if defined(__linux__) || defined(PF_IUCV)
		case PF_IUCV:
			return "iucv";
#endif
#if defined(__linux__) || defined(PF_RXRPC)
		case PF_RXRPC:
			return "rxrpc";
#endif
		case PF_ISDN:
			return "isdn";
#if defined(__linux__) || defined(PF_PHONET)
		case PF_PHONET:
			return "phonet";
#endif
#if defined(__linux__) || defined(PF_IEEE802154)
		case PF_IEEE802154:
			return "ieee802154";
#endif
#if defined(__linux__) || defined(PF_CAIF)
		case PF_CAIF:
			return "caif";
#endif
#if defined(__linux__) || defined(PF_ALG)
		case PF_ALG:
			return "alg";
#endif
#if defined(__linux__) || defined(PF_NFC)
		case PF_NFC:
			return "nfc";
#endif
#if defined(__linux__) || defined(PF_VSOCK)
		case PF_VSOCK:
			return "vsock";
#endif
#if defined(__linux__) || defined(PF_KCM)
		case PF_KCM:
			return "kcm";
#endif
#if defined(__linux__) || defined(PF_QIPCRTR)
		case PF_QIPCRTR:
			return "qipcrtr";
#endif
#if defined(__linux__) || defined(PF_SMC)
		case PF_SMC:
			return "smc";
#endif
#if defined (PF_XDP)
		// 2025-May: defined by glibc but not uClibc
		case PF_XDP:
			return "xdp";
#endif
#ifdef PF_MCTP
		// 2024-July: defined by glibc but not musl
		case PF_MCTP:
			return "mctp";
#endif
		default:
			return "unknown";
	}
}

// Taken from https://github.com/Gandi/packet-journey/blob/master/lib/libnetlink/netlink.c
#define parse_rtattr_nested(tb, max, rta) \
        (parse_rtattr_flags((tb), (max), RTA_DATA(rta), RTA_PAYLOAD(rta), 0))
#define parse_rtattr_one_nested(type, rta) \
	(parse_rtattr_one(type, RTA_DATA(rta), RTA_PAYLOAD(rta)))

static int parse_rtattr_flags(struct rtattr *tb[], int max,
                              struct rtattr *rta, int len,
                              unsigned short flags)
{
	unsigned short type;

	memset(tb, 0, sizeof(struct rtattr *) * (max + 1));
	while (RTA_OK(rta, len)) {
		type = rta->rta_type & ~flags;
		if ((type <= max) && (!tb[type]))
			tb[type] = rta;
		rta = RTA_NEXT(rta, len);
	}
	return 0;
}

#ifdef __linux__
static struct rtattr * __attribute__((pure)) parse_rtattr_one(int type, struct rtattr *rta, int len)
{
	while (RTA_OK(rta, len)) {
		if (rta->rta_type == type)
			return rta;
		rta = RTA_NEXT(rta, len);
	}
	return NULL;
}
#endif
