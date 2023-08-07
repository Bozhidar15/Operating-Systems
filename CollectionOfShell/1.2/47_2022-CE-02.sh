#!/bin/bash

if [ $# -ne 1 ]
then
	echo "ERROR: Arg count"
	exit
fi

if echo "string" | egrep -q "..regex.." ; then
	expr
fi

if [ $(echo "$1" | wc -m) -gt 4 ]
then
	echo "ERROR: Device name too long"
	exit 1
fi

file_name=~/somefile

line=$(cat "$file_name" | grep "$1 ")

if echo "$line" | grep -q "*enabled"
then
	echo "$1" > $file_name
fi


