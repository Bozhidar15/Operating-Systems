#!/bin/bash

if [ $# -ne 3 ]; then
        echo "Invalid input"
        exit 1
fi

if [[ "$(id -u)" -ne 0 ]]; then
        echo "Script must be run by root"
        exit 1
fi

if [[ ! -d $1 || ! -d $2 ]]; then
        echo "Invalid arguments"
        exit 1
fi

if [ $(find $2 -mindepth 1 -maxdepth 2 | wc -l) -ne 0 ]; then
        echo "Destination dir not empty"
        exit 1
fi

find $1 -mindepth 1 -type f -name "*$3*" -printf "%p\n" | xargs -I {} mv {} $2
