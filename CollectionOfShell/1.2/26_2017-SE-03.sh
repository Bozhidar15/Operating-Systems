#!/bin/bash

#if [[ "$(whoami)" != "s0600007" ]]; then
#        echo "This script must be rum by root"
#        exit 1
#fi

for user in $(ps -e -o user=|sort -d|uniq); do
        ps -u $user -o rss=,user=|awk -v sum=0 '{sum+=$1} END {print sum" "$2}'
done

for user in $(ps -e -o uid=|sort -d|uniq); do
        all=$(ps -u $user -o rss=|awk -v sum=0 '{sum+=$1} END {print sum}')
        count=$(ps -u $user -o rss=|wc -l)
        av=$(( all / count ))
        maxAndPid=$(ps -u $user -o rss=,pid=|awk -v max=0 'max<$1 {max=$1} END {print max" "$2}')
        if [[ $(( av * 2 )) -lt $(echo $maxAndPid|cut -d' ' -f1) ]]; then
                kill -9 $(echo $maxAndPid|cut -d' ' -f2)
        fi
done
