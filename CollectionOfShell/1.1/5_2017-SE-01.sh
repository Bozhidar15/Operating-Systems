#!/bin/bash

find . -type f -printf "%n %f\n" | sort -rn | head -5 
#ls -l -i | cut -d ' ' -f 1 | sort | uniq -c | sort -n | head -n 5
