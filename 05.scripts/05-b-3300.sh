#!/bin/bash

read -p "Enter there files separated with space: " file1 file2 file3
paste ${file1} ${file2} | sort > ${file3}
