#!/bin/bash
cut -b 3-5,10-15 text.txt | sed 's/*//g' | sed 's/ //g' | sed 's/\t//g' | wc -c