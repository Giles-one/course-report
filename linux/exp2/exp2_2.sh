#!/bin/bash

if [ "$1" = "" ]
then
    echo "usage: ./exp.sh name"
    exit
fi
for user in $(cut -d : -f 1 /etc/passwd)
do
    if [ $user = $1 ]
    then
        echo "Found user in /etc/passwd"
        exit
    fi
done

echo "user not in /etc/passwd"