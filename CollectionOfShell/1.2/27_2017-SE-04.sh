#!/bin/bash

if [ "${#}" -eq 0 ] || [ "${#}" -gt 2 ]; then
	echo error
	exit 1
fi

count=0
while read dir ex to; do 
	if [ "${ex}" == "N" ]; then 
		count="$(( count + 1 ))"
		continue
	fi
	echo "${dir} -> ${to}"
done < <(find ~ -type l -printf "%p %Y %l\n")
echo "${count}"
