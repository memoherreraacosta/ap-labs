# Lab 0.2 

- Linking process in C 

** Strings manipulation library

The following code "str-main.c" is an implementation of the following methods 
that will be linked with the library "strlib.c" also with the main function 
that runs those functions on values implemented on the code.

* int strlen(char *str);

* *char stradd(char *origin, char *addition);

* int strfind(char *origin, char *substr);

* int main(int argc, char ** argv);

The code "strlib.c" is the code where the functions will be implemented and lately run 
in the "str-main.c" code. 

Call all functions from strlib.c library in a new str-main.c file
Use the following commands for compilation and linking

*  gcc -c str-main.c -o str-main.o
*  gcc -c strlib.c -o strlib.o
*  gcc str-main.o strlib.o -o str-final.o

Your program needs to support the following arguments. Check the expected output:

*  ./str-final.o originalVeryLongString Addition Add
*  Initial Lenght      : 22
*  New String          : originalVeryLongStringAddition
*  SubString was found : yes
