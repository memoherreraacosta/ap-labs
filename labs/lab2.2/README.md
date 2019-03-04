Lab 2.2 - Logger Library
========================


Instructions
------------------------

Implement a Logger library in C that will be used for printing the following types of messages.
- `INFO` General information.
- `WARN` Warnings.
- `ERROR` Errors.
- `PANIC` Panics. Non recoverable issues with core dump.

This `logger` library will be used instead of `printf` function calls in all new labs and challenges that we'll be doing in the course.
Below you can see the prototype for each function.

```
int infof(const char *format, ...)
int warnf(const char *format, ...)
int errorf(const char *format, ...)
int panicf(const char *format, ...)
```

---------------------------
Implementation
---------------------------

This implementation prints 4 outputs; each one with a type that the logger library has ( `INFO` , `WARN` , `ERROR` , `PANIC` ). Those are printed with a different font to identify them.

To run the 'Logger Library' you need to compile the [testLogger.c](./testLogger.c) file with the [logger.c](./logger.c) static library. Then, run the executable object file. 

That is made with the make command

```
$ make
```


General Requirements and Considerations
---------------------------------------

- Have [GCC](https://gcc.gnu.org/install/) installed.
