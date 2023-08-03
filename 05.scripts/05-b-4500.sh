#!/bin/bash

chovek="${1}"
doIt=""
while true ; do 
	if who | grep -q "${chovek}" ; then
		echo "tozi chovek veche e v sistemata!"
		break
	else 
		sleep 1
	fi
done

