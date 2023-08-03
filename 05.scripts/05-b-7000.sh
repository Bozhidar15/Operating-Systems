#!/bin/bash

read -p "Give me a string" str


while [ $# -ne 0 ]; do 
	File=$1
	shift 
	
	echo "${File} $(cat ${File} | grep -F ${str} | wc -l) "
done
