#!/bin/bash

find /usr/ -maxdepth 3 -type f -name '*i.h' -exec wc -l '{}' \;
