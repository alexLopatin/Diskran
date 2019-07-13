#!/bin/bash
rm time.txt
python3 tests.py
for (( i=1; i <= 10; i++ ))
do
	/usr/bin/time -f "%e %M" -ao "time.txt" ./lab7.out "tests/test${i}.txt" T >> time.txt
done
python3 graphic.py