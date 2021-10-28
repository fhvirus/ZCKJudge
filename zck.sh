#!/bin/bash

stime=$(date +"%s%N")

echo "Compiling..."
if [ $5 == 1 ]; then
	g++ "$1" -o "exec/gen"
	g++ "$2" -o "exec/bru"
fi
g++ "$3" -o "exec/sol"
ctime=$(date +"%s%N")
echo "Compilation Completed."
echo "Compilation time: $(((ctime - stime) / 1000000)) ms."

for((i=0;i<$4;i++)); do
	./exec/gen > iof/input.txt
	./exec/bru < iof/input.txt > iof/brute.txt
	./exec/sol < iof/input.txt > iof/solve.txt
	cmp -s "iof/brute.txt" "iof/solve.txt"
	result=$?
	if [ $result == 1 ]; then
		echo "Hack found on # $i"
		echo "Input:"
		cat iof/input.txt
		echo

		echo "BruteForce Output:"
		cat iof/brute.txt
		echo 

		echo "Your solution Output:"
		cat iof/solve.txt
		echo 
		break
	fi
	if [ $(( $i % 128 )) == 0 ]; then 
		echo "Done $i"
	fi
done

ttime=$(date +"%s%N")
echo "Time elapsed: $(((ttime - stime) / 1000000)) ms."

