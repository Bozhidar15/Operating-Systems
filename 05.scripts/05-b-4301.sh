#!/bin/bash

file="${1}"
name="${2}"
nickname="${3}"
username=""

username="$(grep "${name}" /etc/passwd | cut -d ':' -f1)"
echo "${nickname}:${username}" >> ${file}
