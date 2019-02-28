Lab 2.3 - Cross-referencer
==========================

#### Code in C that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. 

#### Remove noise words like :

* the
* and
* a
* an 
* for
* from 
* in
* to
* of 
* at
* also
* that


General Requirements and Considerations
---------------------------------------
- Have [GCC](https://gcc.gnu.org/install/) installed.
- Have a text file to test (or use those text files in the repository)



How to run it?
----------
1. Clone or download this current repository
2. Move inside the directory in your terminal and run the following command to compile the C files 

```
$ make
```

3. To run it run the following command 
```
$ ./cross-ref [your document to be read]
```

4. If you want to use the repositorie´ stest cases, run the following command

```
$ ./cross-ref irving-little-573.txt
```
				for [irving-little-573.txt](./irving-little-573.txt) 
	
```
$ -/cross-ref irving-london-598.txt
```
				for [irving-london-598.txt](./irving-london-598.txt)


