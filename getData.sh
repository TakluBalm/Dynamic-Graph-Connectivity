#! /bin/bash
rm *.txt
var=32;
for i in {1..15}
do
    python generateTest.py  $var
    ./brute; ./graph;
    python checker.py;
    if [ $var -gt 512 ] 
    then
        var=$((var*2));
    else
        var=$((var*4));
    fi
done