#!/bin/bash

if [[ "${#}" -ne 2 ]] || egrep -q '[^0-9]' <(echo "${2}") ; then
	echo "Error"
	exit 1
fi

dirname="$1"
number="$2"

while read size name; do 
	if [[ ${size} -gt ${number} ]]; then 
		echo "${name}"
	fi
done < <(find "${dirname}" -type f -printf "%s %f\n")
