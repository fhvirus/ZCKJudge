# A local judge for debugging

### Usage

```
./zck [generator file] [bruteforce solution] [solution to be tested] [# of testcase] [flag]
```

If flag is set to `1`, it will compile generator and bruteforce solution.
If you don't need to do that, simply set it to `0`.

### Possible Output

This is the output when testing CF 1601E:
```
Compiling...
Compilation Completed.
Compilation time: 5174 ms.
Done 0
Hack found on # 15
Input:
7 4 1
10 83 63 96 6 19 21
2 4
1 2
3 5
1 5

BruteForce Output:
209
20
132
46

Your solution Output:
146
10
126
40
```

The `gen.cpp`, `bru.cpp`, `sol.cpp` are the code for testing and to be tested.
