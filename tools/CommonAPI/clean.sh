#!/bin/bash

if [ $? -ne 0 ]; then /bin/bash -c "$0"; exit; fi

make clean

echo "-------------------------------------"
read -n1 -r -p "Script finalized :-)" key
