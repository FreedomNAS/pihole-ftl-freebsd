#!/usr/bin/env bats
# shellcheck disable=SC2154  # Disable warning about unreferenced variables

# In case of test failure post the whole output of the run command
bats::on_failure() {
    printf "\n"
    printf "═══════════════════════════════════════════════════════════════════════════════\n"
    printf "                              BATS TEST FAILURE DEBUG                         \n"
    printf "═══════════════════════════════════════════════════════════════════════════════\n"
    printf "\n"
    printf "   TEST DESCRIPTION:\n"
    printf "   %s\n" "${BATS_TEST_DESCRIPTION}"
    printf "\n"
    printf "   COMMAND EXECUTED:\n"
    printf "   %s\n" "${BATS_RUN_COMMAND}"
    printf "\n"
    printf "   OUTPUT CAPTURED:\n"

    printf "   %s\n" "${output}"
    printf "\n"
    printf "═══════════════════════════════════════════════════════════════════════════════\n"
    printf "\n"
}

# Runs a shell command as user pihole. FreeBSD's su has no -s (and -c names a
# login class there), -m keeps the caller's shell instead
as_pihole() {
    if [[ "$(uname -s)" == "FreeBSD" ]]; then
        su -m pihole -c "$1"
    else
        su pihole -s /bin/sh -c "$1"
    fi
}
export -f as_pihole

# Name of the loopback interface
LO="lo"
[[ "$(uname -s)" == "FreeBSD" ]] && LO="lo0"
export LO
