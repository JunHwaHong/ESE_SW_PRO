CC=gcc
CFLAGS=-c
INC_PATH=-I../include
LIB_PATH=-L../lib
INK_PATH=-lfuncs -lmysqlclient
OUTPUT=mytest
OBJS=mytest.o

$(OUTPUT) : $(OBJS)
	$(CC) -o $(OUTPUT) $(LIB_PATH) mytest.o $(INK_PATH)

mytest.o : mytest.c
	$(CC) $(CFLAGS) $(INC_PATH)  mytest.c -o mytest.o

clean :
	rm -f $(OBJS) $(OUTPUT)
