CC=gcc
CFLAGS=-c
INC_PATH=-I../include
LIB_PATH=-L../lib
INK_PATH=-lfuncs -lmysqlclient
OUTPUT=mytest
OBJS=mytest.o
SRC=mytest.c

$(OUTPUT) : $(OBJS)
	$(CC) -o ../$(OUTPUT) $(LIB_PATH) $(OBJS) $(INK_PATH)

$(OBJS) : $(SRC)
	$(CC) $(CFLAGS) $(INC_PATH) $(SRC) -o $(OBJS)

clean :
	rm -f $(OBJS) $(OUTPUT)
