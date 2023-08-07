#!/bin/bash

if [[ "${#}" -ne 1 || $(id -u) -ne 0 ]]; then 
	echo error
	exit 1
fi

user="${1}"
uPs="$( ps -u ${user} | tail -n +2 | wc -l )"

ps -e -o user | sort | uniq -c | awk -v ch="${uPs}" '{if ($1 >= ch)print $2}'

avrg="$(ps -e -o time | tail -n +2 | awk -F':' '{lines += 1; sec += $3 + 60*$2 + 3600*$1}END{sec/=lines; print strftime("%H:%M:%S", sec, 1)}')"

sec="$(echo "${avrg}" | awk -F: '{print ($1 * 3600 + $2 * 60 + $3)}')"

while read i r; do 
	currSec="$(echo "${i}" | awk -F: '{print ($1 * 3600 + $2 * 60 + $3)}')"
	if [[ "${currSec}" -gt "${sec}" ]]; then 
		kill -9 "${r}"
	fi

done < <(ps -u ${user} -o time,pid )

