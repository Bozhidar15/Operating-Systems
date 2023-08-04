#!/bin/bash 

numbers=""
while read line; do
	curr="${line}"
	if echo "${curr}" | cut -d ':' -f 5 | grep -q ',И' && echo "${curr}" | cut -d ':' -f 5 | grep -q 'а,' ; then 
		echo "${curr}" | cut -d ':' -f 1 | cut -c 3,4 >> fn.tmp
		echo "${curr}"
	fi

done < /etc/passwd

cat fn.tmp | sort | uniq -c | sort -nr | head -1
rm fn.tmp
