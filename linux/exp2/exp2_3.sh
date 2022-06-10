#!/bin/bash

declare -i score

while true
do
    echo "please input score"
    read score
    res=$[$score/10]
    case $res in
        9|10)   echo "very good"
                ;;
        8)      echo "Good"
                ;;
        7)      echo "not good"
                ;;
        6)      echo "not bad"
                ;;
        *)      echo "bad"
                ;;

    esac
done