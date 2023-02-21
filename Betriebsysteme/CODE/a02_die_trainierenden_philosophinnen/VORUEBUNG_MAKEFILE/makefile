# MAKEFILE FOR critsect02
#

EXE = critsect02


CC = /usr/bin/gcc

CFLAG  = -pthread
CFLAG += -g
CFLAG += -Wall

LDFLAG = -lpthread

SRC = critsect02.c

# targets (all is the default, because its on top.)

all: $(EXE)

run: $(EXE)
	./$(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAG) $(LDFLAG) -o $@ $<

clean:
	rm -f $(EXE)
