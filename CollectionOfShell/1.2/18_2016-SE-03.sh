#!/bin/bash

if [[ "${#}" -ne 2 ]] || egrep -q '[^0-9]' <(echo "${1}${2}") ;then 
	echo "error"
	exit 1
fi

mkdir a b c

for i in $(find . -mindepth 1 -maxdepth 1 -type f) ; do 
	lines="$(cat "${i}" | wc -l)" 
	if [[ "${lines}" -lt "${1}" ]]; then 
		mv "${i}" ./a
		continue
	fi
	if [[ "${lines}" -le "${2}" ]] && [[ "${lines}" -ge "${1}" ]]; then 
		mv "${i}" ./b
	else
		mv "${i}" ./c
	fi
done 
