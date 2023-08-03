#!/bin/bash 
#
read -p "Enter full path: " dir

countFiles=$(find "${dir}" -mindepth 1 -type f 2>/dev/null |wc -l)
countDirs=$(find "${dir}" -mindepth 1 -type d 2>/dev/null |wc -l)

echo "Files count is ${countFiles}. Dirs count is ${countDirs}"
