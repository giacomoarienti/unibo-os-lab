#!/bin/bash
TIME=$1
while [[ $TIME -gt "0" ]]; do
    sleep 1
    echo -n "."
    ((TIME=${TIME}-1))
done
echo