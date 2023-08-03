#!/bin/bash

if echo "${1}" | grep '[^a-zA-Z0-9]'; then 
	echo "Not alphabetic"

else
	echo "Ok"
fi
