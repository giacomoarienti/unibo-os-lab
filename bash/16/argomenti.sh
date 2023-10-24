#!/bin/bash
PARI=""
DISPARI=""

for ((NUM=2; $NUM<=$#; NUM=$NUM+2)); do
    PARI="$PARI ${!NUM}"
done

for ((NUM=1; $NUM<=$#; NUM=$NUM+2)); do
    DISPARI="$DISPARI ${!NUM}"
done

echo $PARI
echo $DISPARI