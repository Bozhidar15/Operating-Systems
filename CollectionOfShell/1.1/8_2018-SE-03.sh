#!/bin/bash

group=$(cat /etc/passwd | sed -n '201p' | cut -d ':' -f 4)
pp=$(cat /etc/passwd | awk -F ':' -v g=$group '$4==g {print $0}')
echo "${pp}" | egrep '(,СИ|,SI)' | cut -d ':' -f 5,6 | tr -s ',' | sed -E 's/:/,/g' | cut -d ',' -f 1,3 | sed 's/,/:/g' | sort -t ':' -n -k 2.17,2.24
