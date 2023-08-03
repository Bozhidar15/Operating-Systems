#!/bin/bash

if [[ "${#}" -ne 1 ]]; then 
	echo "error"
	exit 1
fi

fk="${1}"

while read r v; do 
	echo "scale=2; ${r}/${v}" | bc
done < <(ps -o rss=,vsz= -u "${fk}" | tr -s ' ') | sort -nr

