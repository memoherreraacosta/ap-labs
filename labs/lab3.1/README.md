Lab 3.1 - File/Directory Monitor
================================

Write a program that logs all file creations, deletions, and renames under the directory named in its command-line argument.
The program should monitor events in all of the subdirectories under the specified directory.
To obtain a list of all of these subdirectories, you will need to make use of [nftw()](https://linux.die.net/man/3/nftw).
When a new subdirectory is added under the tree or a directory is deleted, the set of monitored subdirectories should be updated accordingly.

General Requirements and Considerations
---------------------------------------

- Have [GCC](https://gcc.gnu.org/install/) installed

Implementation 
---------------------------------------

- Run the following command to build 
```
$ make
```

- To clean the files, run the following command
```
$ make clean
```

- To run it, write down the following command 
```
$ make && ./monitor [tree of directories to watch]
```
