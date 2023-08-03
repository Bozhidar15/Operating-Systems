#!/bin/bash

read -p "Enter your name " name

num_sessions="$(who | grep "${name}" | wc -l)"

echo "User ${name} has ${num_sessions} sessions."

