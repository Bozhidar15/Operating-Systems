#!/bin/bash

if [[ "${#}" -ne 1 ]]; then 
	echo "error"
	exit 1
fi

user="${1}"
numberOf="$(ps -u ${user} | tail -n +2 | wc -l)"
while read pid; do 
	kill -9 "${pid}"
done < <(ps -u ${user} | tail -n +2 | awk '{print $1}')
echo "this user had ${numberOf} processes"
# this script wouldn't work because students don't have that kind of permissions

