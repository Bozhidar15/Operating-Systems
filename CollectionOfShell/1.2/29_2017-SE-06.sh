#!/bin/bash

function has_homedir {
	if [ -z "$1" ]; then
		return 0
	fi
}

function not_dir {
	if [ ! -d "$1" ]; then
		return 0
	fi
}
function no_owner {
	if [ $1 != $2 ]; then
		return 0
	fi
}
function write {
	if [ $(echo "${1}" |cut -c 3) != "w" ]; then
		return 0
	fi
}
function check_home {
	user="${1}"
	uid="${2}"
	home=$(cat /etc/passwd | grep "${user}" |cut -d':' -f 6)


	dirperm=$(ls -ld $home | awk '{print $1}')
	dirowner=$(ls -ld $home | awk '{print $3}')
	

	if has_homedir "${home}" || not_dir "${home}" || no_owner "${dirowner}" "${user}" || write "${dirperm}"
		return 0
	else
		return 1
	fi
}
curr=""
all=0
rootAll="$(ps -u root -o rss| tail -n +2 | awk '{sum+=$1}END{print sum}')"
while read user u; do
	if check "${user}" "${u}"; then 
		if [ "${curr}" != "${u}" ]; then
			if [ "$(ps -u "${user}" -o rss| tail -n +2| awk '{sum+=$1}END{print sum}')" -gt "${rootAll}" ]; then
				ps -u "${user}" -o pid | xargs -I @ kill -9 @
			fi
		fi
	else
		continue
	fi


done < <(comm -1 -3 <(ps -u root -o user,uid|tail -n +2| sort -k2|uniq) <(ps -e -o user,uid|tail -n +2 | sort -k2 | uniq))
