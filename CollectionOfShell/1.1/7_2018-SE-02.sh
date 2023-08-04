#!/bin/bash


find "${1}" -type f -printf "%A@ %f %i\n" | sort -nr | cut -d ' ' -f 3 | head -1 
