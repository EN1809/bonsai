#! /bin/bash

RunningInInteractiveTerminal=0

if [ -t 1 ]; then
 echo "Running in an interactive terminal."
 RunningInInteractiveTerminal=1
fi
