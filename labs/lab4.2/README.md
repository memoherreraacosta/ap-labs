Lab 4.2 - Matrix Multiplication
===============================

On this lab, its shown an implementation of multi-threaded matrix multiplicator with the usage of the `pthreads` library. 


Concepts used in the lab:

- Multitheading
- Synchronization mechanisms
- Race conditions


General instructions
--------------------

1. The program receives one argument which will be know as `NUM_BUFFERS` inside the program (e.g. `./multipler -n 8`).
2. It will read a couple of files (`matA.dat`, `matB.dat`) which contain data that will be used for the matrices multiplication. It's an array that represents all matrix's rows in an one-dimension array.


Matrix multiplication
---------------------

- This implementation has a loop that is creating NxN (2000*2000) threads in lots of 2000 concurrent processes for calculating the `row*col` operations between `matA` and `matB`.
- The idea of having 2000 concurrent processes is to play with the synchronization of the "limited" memory you have with the defined number of buffers (`NUM_BUFFERS`).
- Each thread will execute `row*col` operation and will use available 2 buffers for temporaly storing the 2 arrays that are required for calculating the dot product.
`getLock` function will be required to get a buffer for storing a vector, if there's no available buffer, thread will need to wait.
`releaseLock` will be used to release a buffer to be used by another thread.
- At the end, It'll wait for all processes to join the main execution.
- Each lot of 2000 threads goal will represent a row in the final matrices multiplication result.

Data files
----------

- [matA.dat](https://github.com/memoherreraacosta/ap-labs/tree/master/labs/lab4.2/matA.dat) 

- [matB.dat](https://github.com/memoherreraacosta/ap-labs/tree/master/labs/lab4.2/matB.dat)



How to build and run it
==================

1. To build 
```

$ make

```

2. To Run


" $ ./multipler -n 'NUM_BUFFERS' "

 + It is recomended to use a number bigger than 8 and smaller than 100 to have an optimum resources handling in execution. 

Example: 

```

$ ./multipler -n 8

```
