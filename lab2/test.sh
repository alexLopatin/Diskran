#!/bin/bash
rm time.txt
python3 tests.py
for (( i=1; i <= 35; i++ ))
do
	/usr/bin/time -f "%e %M" -ao "time.txt" ./a.out "tests/test${i}0000.txt" T >> time.txt
done
python3 graphic.py