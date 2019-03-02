all: 
	gcc testLogger.c -o testLogger.o
	gcc logger.c -o logger.o
	gcc testLogger.o logger.o -o loggerFinal.o
	./loggerFinal.o
remove:
	($rm) logger.o testLogger.o loggerFinal.o
