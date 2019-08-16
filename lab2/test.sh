#!/bin/bash
rm InsertTime.txt
rm SearchTime.txt
python3 tests.py
for (( i=1; i <= 10; i++ ))
do
	/usr/bin/time -f "%e %M" -ao "InsertTime.txt" ./lab2.out "tests/test${i}000.txt" "tests/result.txt" >> time.txt
done
python3 graphic.py InsertTime.txt
python3 SearchTests.py
for (( i=1; i <= 10; i++ ))
do
	/usr/bin/time -f "%e %M" -ao "SearchTime.txt" ./lab2.out "tests/test${i}000.txt" "tests/result.txt" >> time.txt
done
python3 graphic.py SearchTime.txt