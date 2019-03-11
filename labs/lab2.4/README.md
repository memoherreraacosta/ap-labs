Lab 2.4 - Add `syslog` support to your Logger
=============================================

Instructions
---------------------------------------

Now it's time to add support for Linux system logging into your logger that you implemented on [lab2.2](https://github.com/memoherreraacosta/ap-labs/tree/master/labs/lab2.2).

A new `initLogger`function will be added in order to add support for choosing between `stdout` or `syslog` logging.

```
int initLogger(char *logType)
```

You will handle the following log types:
- `stdout` or empty string for `STDOUT` logging
- `syslog` for `SYSLOG` logging



General Requirements and Considerations
---------------------------------------

- Have [GCC](https://gcc.gnu.org/install/) installed.



Implementation
---------------------------

This implementation prints 12 outputs, 3 blocks of 4 outputs; each block prints a type that the logger library has ( `INFO` , `WARN` , `ERROR` , `PANIC` ). 
Each block also has an implementation of the *initLogger* function;

-  one as *DEFAULT*, the other as *STDOUT* and *SYSLOG*. 

Those are printed with a different font to identify them.

To run the 'Logger Library' you need to compile the [testLogger.c](./testLogger.c) file with the [logger.c](./logger.c) static library. Then, run the executable object file. 

That is made with the make command
```
$ make
```
