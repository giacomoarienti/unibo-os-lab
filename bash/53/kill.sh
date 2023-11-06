#!/bin/bash
./puntini.sh 30 &
PNTPID=$!
sleep 5
kill -9 $PNTPID 