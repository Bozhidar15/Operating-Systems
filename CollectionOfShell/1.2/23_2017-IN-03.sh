#!/bin/bash

all="$(find /home/students -not -path "*/." -type f -printf "%T@ %h/%f\n" 2> /dev/null | sort -nr -k1 | head -1 )"
path="$(echo "${all}" | cut -d ' ' -f 2)"

echo "$(echo "${path}" | sed -E 's%.*students/([^/]*).*%\1%g')"

echo "${path}"
