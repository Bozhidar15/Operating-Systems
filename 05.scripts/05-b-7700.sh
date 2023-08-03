#!/bin/bash

if [[ "${#}" -ne 2 ]] || grep -E -q '[^0-9]' <(echo "${2}"); then 
	echo "error"
	exit 1
fi

count=0
while read size; do 
	if [[ "${size}" -gt "${2}" ]]; then 
		count="$((count + ${size}))"
	fi
done < <(find "${1}" -type f -printf "%s\n")
echo "${count}"
