# MAKEFILE FOR critsect02
#
EXE=prog

CC = /usr/bin/gcc


CFLAG  = -pthread
CFLAG += -g
CFLAG += -Wall -ansi
#CFLAG += -std=gnu99

LDFLAG = -lpthread

OBJ = main.o gym.o philo.o global.o
SRC = $(OBJ:%.o=%.c)

DEPENDFILE = .depend


$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAG) -o $(EXE) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

ifeq ($(DEPENDFILE),$(wildcard $(DEPENDFILE)))
-include $(DEPENDFILE)
endif

clean:
	rm -f $(DEPENDFILE) $(EXE) $(OBJ)

dep depend $(DEPENDFILE):
	$(CC) $(CFLAGS) -MM *.c > $(DEPENDFILE)
