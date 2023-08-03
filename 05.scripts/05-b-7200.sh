#!/bin/bash

if [[ ${#} -eq 0 ]]; then 
	echo "error"
	exit 1
fi

#while [[ "${#}" -ne 0 ]]; do
#i="${1}"
#shift
for i in <(seq 1 "${#}"); do
	if [[ -d "${i}" ]]; then 
		numofFiles="$(find "${i}" -type f | wc -l)"
		while read size name; do 
			if [[ "${numofFiles}" -gt "${size}" ]]; then 
				echo "${name}"
			fi
		done < <(find "${i}" -type f -printf "%s %p\n")
		continue
	fi

	if [[ -r "${i}" ]]; then
		echo "this file has read access"
	fi
	
done
	


