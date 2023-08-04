#!/bin/bash

i=$(find . -type f -printf "%T@ %p %i\n" | sort -n | head -n 1 | cut -d ' ' -f 3)

d=$(find . -type f -printf "%T@ %p %i\n" | sort -n | head -n 1 | cut -d ' ' -f 2)

count=0

for 
