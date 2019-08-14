#!/bin/bash
rm time.txt
python3 tests.py
for (( i=1; i <= 10; i++ ))
do
	/usr/bin/time -f "%e %M" -ao "time.txt" ./lab9.out "tests/test${i}.txt" "tests/result.txt" >> time.txt
done
python3 graphic.py