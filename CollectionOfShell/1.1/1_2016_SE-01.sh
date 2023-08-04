#!/bin/bash

file="${1}"
first="$(cat "${file}" | grep -E -c '[02468]')"
second="$(cat "${file}" | egrep '[02468]' | egrep -c '[a-w]')"
#second="$(cat "${file}" | egrep -c '([02468]{1,}&[a-w]{1,})')"
echo "$(echo "${first} - ${second}" | bc)"
