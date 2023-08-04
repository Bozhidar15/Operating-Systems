#!/bin/bash

find /home/students -mindepth 1 -maxdepth 1 -type d -printf "%C@\t%f\n" | awk '{if ($1 > 1551168000 && $1 < 1551176100) print $0 }'
