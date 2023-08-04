#!/bin/bash

num="${1}"

temp_file="$(mktemp)"

ps -e -o user=,pid=,rss= > "${temp_file}"

for user in $(cat "${temp_file}"|tr -s ' ' | cut -d " " -f 1 | sort | uniq); do
	read mem_used max_pid < <(awk -v user="${user}" \
		'	BEGIN{count=0; max_mem=-1; max_pid=-1}
			$1 == user { count += $3 } 
			$1 == user && $3 > max_mem { max_mem = $3; max_pid = $2 }
			END {print count, max_pid}
			' "${temp_file}")
	
	echo "user ${user} has used ${mem_used} memory and max_pid is ${max_pid}"
	if [[ ${mem_used} -ge ${1} ]]; then
		echo "will kill ${max_pid}"
	fi
done

rm "${temp_file}"

