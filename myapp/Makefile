CC=gcc
CFLAGS=-c
INC_PATH=-I../include
LIB_PATH=-L../lib
INK_PATH=-lfuncs -lmysqlclient
OUTPUT=WorkOut
OBJS=workout.o

$(OUTPUT) : $(OBJS)
	$(CC) -o $(OUTPUT) $(LIB_PATH) mytest.o $(INK_PATH)

mytest.o : workout.c
	$(CC) $(CFLAGS) $(INC_PATH)  workout.c -o workout.o

clean :
	rm -f $(OBJS) $(OUTPUT)
