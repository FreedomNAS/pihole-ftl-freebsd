#!/bin/bash
# Test script to test names returned for local interfaces
# The logic of this mechanism has been extracted from piholeDebug.sh

getIPs() {
    local dig_result addr
    local addr_type
    addr_type=$1
    local protocol
    protocol=$2

    if [[ "$(uname -s)" == "FreeBSD" ]]; then
        # Leave out 127.0.0.2 and up, which only stand in for the loopback
        # network Linux answers on as a whole (test/run.sh), and link-local
        # addresses, which come with a %scope
        addresses="$(ifconfig -a "${addr_type}" | awk -v t="${addr_type}" '$1 == t && $2 !~ /^127\.0\.0\.([2-9]|[1-9][0-9]+)$/ && $2 !~ /%/ { print $2 }')"
    else
        addresses="$(ip address show | sed "/${addr_type} /!d;s/^.*${addr_type} //g;s/\/.*$//g;")"
    fi
    if [ -n "${addresses}" ]; then
        while IFS= read -r addr ; do
            # Check if Pi-hole can use itself to block a domain
            dig_result=$(dig +tries=1 +time=2 -x "${addr}" @127.0.0.1 +short)
            if [[ $addr == "127.0.0.1" && $dig_result == "localhost." ]] || [[ $addr == "::1" && ( $dig_result == "localhost." || $dig_result == "ip6-localhost." ) ]] || [[ $dig_result == "pi.hole." ]]; then
                echo "${addr} is \"${dig_result}\": OK"
            else
                # Otherwise, show a failure
                echo "${addr}: ERROR"
                echo "${dig_result}"
                echo ""
            fi
        done <<< "${addresses}"
    fi
}

# Test PTR responses on all available IPv4 addresses
getIPs inet 4
# Test PTR responses on all available IPv6 addresses
getIPs inet6 6
