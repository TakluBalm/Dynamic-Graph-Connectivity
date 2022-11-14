#! /bin/bash
for i in {1..100} 
do
python generateTest.py;
./brute; ./graph;
python checker.py;
if [ $? == 1 ]; then
	break
fi
done