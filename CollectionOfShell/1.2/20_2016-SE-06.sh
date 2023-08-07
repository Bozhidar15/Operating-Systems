#!/bin/bash

if [[ "${#}" -ne 1 ]]; then 
	echo error
	exit 1
fi
cnt=0
cat "${1}" | awk '{cnt += 1; $1=""; $2= cnt". "; print $0}' | sort -k 3
# {
# 	while read line; do 
# 		cnt=$(( cnt + 1 ))
# 		echo "${line}" | awk -v ch="${cnt}." '{$1=""; $2=ch; print $0}'
# 	done < <(cat "${1}")
# } | sort -k 3
