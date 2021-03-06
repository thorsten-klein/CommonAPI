#!/bin/bash

if [ $? -ne 0 ]; then /bin/bash -c "$0"; exit; fi

#######################################################
# Function: Wait for any key and exit 
#######################################################
function wait_and_exit {
	echo
	echo "----------------------------------------------------"
	read -n1 -r -p "Waiting for any key to exit ..." key
	exit
}


#######################################################
# Code
#######################################################
rm -rf ./*
git reset --hard

#######################################################
# FINALIZE
#######################################################
wait_and_exit
