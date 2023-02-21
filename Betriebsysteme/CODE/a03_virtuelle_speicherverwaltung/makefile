# MAKEFILE
########################## EXE
MMANAGE_EXE = mmanage
VMAPPL_EXE  = vmappl
EXE         = $(MMANAGE_EXE) $(VMAPPL_EXE)
########################## COMPLIER 
CC = /usr/bin/gcc

CFLAG  = -pthread
CFLAG += -g
CFLAG += -Wall
#CFLAG += -DDEBUG_MESSAGES

LDFLAG = -lpthread
########################## TURN OFF SUFFX RULES
.SUFFIXES:
########################## DIRECTORIES
SRCPATH = SRC/
HDRPATH = SRC/
OBJPATH = OBJ/

vpath %.c $(SRCPATH)
#vpath %.h $(HDRPATH)

DEPFILE = .depend

HDR= $(wildcard $(HDRPATH)*.h)

SRC_MMANAGE = $(wildcard $(SRCPATH)mm*.c)
SRC_VMAPPL  = $(wildcard $(SRCPATH)vm*.c)
SRC         = $(SRC_MMANAGE) $(SRC_VMAPPL) 

_OBJ_NOSUFFIX = $(notdir $(basename $(SRC)))

_OBJ_MMANAGE = $(notdir $(SRC_MMANAGE:.c=.o))
_OBJ_VMAPPL  = $(notdir $(SRC_VMAPPL:.c=.o))


OBJ_MMANAGE = $(addprefix $(OBJPATH),$(_OBJ_MMANAGE))
OBJ_VMAPPL  = $(addprefix $(OBJPATH),$(_OBJ_VMAPPL))
OBJ         = $(OBJ_MMANAGE) $(OBJ_VMAPPL)
############################################## SPECIAL
.SILENT: info dep
.PHONY: clean
############################################### TARGET
run_all: run_fifo run_clock run_lru
#
all: $(EXE)
#
run_fifo: $(EXE)
	./$(MMANAGE_EXE) --fifo &
	sleep 1
	./$(VMAPPL_EXE)
	pkill -INT $(MMANAGE_EXE) 
	mv ./LOG/logfile.txt ./LOG/fifo.txt
	mv pagefile.bin fifo.bin
#
run_clock: $(EXE)
	./$(MMANAGE_EXE) --clock &
	sleep 1
	./$(VMAPPL_EXE)
	pkill -INT $(MMANAGE_EXE) 
	mv ./LOG/logfile.txt ./LOG/clock.txt
	mv pagefile.bin clock.bin
#
run_lru: $(EXE)
	./$(MMANAGE_EXE) --lru &
	sleep 1
	./$(VMAPPL_EXE) > /dev/null
	pkill -INT $(MMANAGE_EXE) 
	mv ./LOG/logfile.txt ./LOG/lru.txt
	mv pagefile.bin lru.bin
# ---------------------------------------- info print
info: dep 
	echo =============== SRC ===============
	echo $(SRC)
	echo =============== HDR ===============
	echo $(HDR)
	echo =============== OBJ ===============
	echo $(OBJ)
	echo $(OBJ_VMAPPL)
	echo $(OBJ_MMANAGE)
	echo ========== OBJ_NOSUFFIX ===========
	echo $(_OBJ_NOSUFFIX)
	echo =============== DEP ===============
	cat $(DEPFILE)
#------------------------------------------COMPILING
$(OBJPATH)%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@
#--------------------------------------------LINKING
$(MMANAGE_EXE): $(OBJ_MMANAGE)
	$(CC) $(CFLAG) $(LDFLAG) -o $(MMANAGE_EXE) $?
$(VMAPPL_EXE): $(OBJ_VMAPPL)
	$(CC) $(CFLAG) $(LSFLAG) -o $(VMAPPL_EXE) $?
######################################### DEPENDENCIES
-include $(DEPFILE)
#---------------------------------------- DEPENDENCIES
dep: $(HDR) $(SRC) 
	echo ========= create .depend ==========
	> $(DEPFILE)
	$(foreach obj,                       \
	          $(_OBJ_NOSUFFIX),          \
		  $(CC) $(CFLAG)             \
		      -MM $(SRCPATH)$(obj).c \
		      -MQ $(OBJPATH)$(obj).o \
		      >> $(DEPFILE);         \
	)
#--------------------------------------------- CLEAN
clean:
	rm -f $(DEPFILE) $(EXE) $(OBJ) *.bin LOG/*.txt
