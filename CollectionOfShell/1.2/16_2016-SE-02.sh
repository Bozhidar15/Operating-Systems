#!/bin/bash
if [ $# -ne 1 -o $(id -u) -ne 0 ]; then
	exit 1
fi
users=$(ps -e -o user | tail -n +2 | sort | uniq)
for user in $users; do
	total_rss=0
	while read line; do
		current_pid=$(echo $line|awk '{print $1}')
		current_rss=$(echo $line|awk '{print $2}')
		total_rss=$(expr $total_rss + $current_rss)
	done < <(ps -u $user -o pid,rss | tail -n +2 | sort -n -k 2)
	
	echo "user:" $user "total_rss:" $total_rss
	
	if [ $total_rss -gt $1 ]; then
		echo "greater than $1, will kill $current_pid"
		kill -s SIGTERM $current_pid
		sleep 2
		kill -s SIGKILL $current_pid
	fi
done
