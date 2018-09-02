#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <CPA file> <VDA file>"
    exit -1
fi

COMPLETE_FILE=".complete"
tail -n +2 $1 > $COMPLETE_FILE
tail -n +2 $2 >> $COMPLETE_FILE

MOST_LIQUID=$(cat $COMPLETE_FILE | cut -f2 -d\; | sort | uniq -c | sort -k1gr | head -n1 | xargs | cut -f2 -d' ')
rm -rf $COMPLETE_FILE
echo $MOST_LIQUID

grep $MOST_LIQUID $1 > $(basename $1 | cut -f1 -d. )_most_liquid.txt
grep $MOST_LIQUID $2 > $(basename $2 | cut -f1 -d. )_most_liquid.txt
