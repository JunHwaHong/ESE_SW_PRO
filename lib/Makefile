CC=gcc
CFLAGS=-c
AR=ar
ARFLAGS=rv
OUTPUTLIB=libfuncs.a
OBJS=show_window.o action_db.o action_Coach.o action_Novice.o
INC_PATH=-I../include
.SUFFIXES: .o .c

$(OUTPUTLIB) : $(OBJS)
	$(AR) $(ARFLAGS) $(OUTPUTLIB) $(OBJS)

action_db.o : action_db.c
	$(CC) $(CFLAGS) $(INC_PATH) action_db.c -o action_db.o -lmysqlclient

action_Coach.o : action_Coach.c
	$(CC) $(CFLAGS) $(INC_PATH) action_Coach.c -o action_Coach.o -lmysqlclient

action_Novice.o : action_Novice.c
	$(CC) $(CFLAGS) $(INC_PATH) action_Novice.c -o action_Novice.o -lmysqlclient

show_window.o : show_window.c
	$(CC) $(CFLAGS) $(INC_PATH) show_window.c -o show_window.o

clean :
	rm -f $(OBJS) $(OUTPUTLIB)
