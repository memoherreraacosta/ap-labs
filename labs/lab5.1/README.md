Lab 5.1 - OpenMP Labs
=====================

This is a single lab for multiple OpenMP exercises. 
Below you can see the list of exercises that
will considered for the lab's grading. 
The goal of each exercise is to convert its default serial implementation to
a parallel implementation with [OpenMP](https://computing.llnl.gov/tutorials/openMP/#Introduction).


Exercises :
---------------------------------------

| Exercise Name          | Serial Implementation | Parallel Implementation                            |
|------------------------|-----------------------|----------------------------------------------------|
| Hello World            | [hello.c](hello.c)             | [hello_par.c](hello_par.c)                                     |
| Integral PI Compute    | [pi.c](pi.c)                | [pi_spmd_simple.c](pi_spmd_simple.c), [pi_spmd_final.c](pi_spmd_final.c), [pi_loop.c](pi_loop.c) |
| Monte Carlo PI Compute | [pi_mc.c](pi_mc.c)             | [pi_mc_par.c](pi_mc_par.c)                                      |
| Matrix Multiplication  | [matmul.c](matmul.c)            | [matmul_par.c](matmul_par.c)                                     |
| Producer/Consumer      | [prod_cons.c](prod_cons.c)         | [prod_cons_par.c](prod_cons_par.c)                                  |


Build and Run :
---------------------------------------

* To Build all the implementations, write down the following command

````
    $ make 
````

* To run an implementation, write down the following command

````
    $ ./[ NAME_OF_THE_FILE ]
````

    Example :

````
    $ ./pi_mc_par.c
````
