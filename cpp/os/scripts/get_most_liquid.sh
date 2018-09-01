#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <VDA file> <CDA file>"
    exit -1
fi
COMPLETE_FILE=".complete"
tail -n +2 $1 > $COMPLETE_FILE
tail -n +2 $2 >> $COMPLETE_FILE

cat $COMPLETE_FILE | cut -f2 -d\; | sort | uniq -c | sort -k1gr | head -n1 | cut -f2 -d' '
