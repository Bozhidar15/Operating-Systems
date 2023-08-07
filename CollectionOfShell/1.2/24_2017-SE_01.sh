#!/bin/bash

if [ "${#}" -eq 0 ] || [ "${#}" -gt 2 ]; then 
	echo error
	exit 1
fi

dir="${1}"
number=0
if [ "${#}" -eq 2 ]; then
	number="${2}"
	while read num file i; do 
		if [ "${num}" -ge "${number}" ]; then 
			echo "${file}"
		fi
	done < <( find "${dir}" -type f -printf "%p %i\n" | sort -n -k2 | uniq -c -f 1 | tr -s ' ' )
else
	while read i file; do 
		if [ "${i}" == N ]; then
			echo "${file}"
		fi
	done < <(find ${dir} -type l -printf "%Y %p\n")
fi


