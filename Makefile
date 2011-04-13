
DEBUG_FLAGS=-g -DDEBUG -Wall
PC_FLAGS=-DPC
ARDUINO_FLAGS=-DARDUINO
GROUP_LIBS=-Lstab/lib -Lsched/lib -lsched -lstab

# INCLUDES holds paths to other groups headers
INCLUDES=../../stab/src

# EXTRA_FLAGS defines what groups code to use instead of stubs
EXTRA_FLAGS=

# PROG is the name of the executable
PROG=prog

export CFLAGS
export CC

BIN:$(OBJS)


pc: CC=gcc
pc: CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) -I$(INCLUDES)
pc:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	$(CC) -c main.c -Isched/src
	$(CC) -o $(PROG) main.o $(GROUP_LIBS)
	

pc-dbg: CC=gcc
pc-dbg: CFLAGS+=$(PC_FLAGS) $(EXTRA_FLAGS) $(DEBUG_FLAGS) -I$(INCLUDES)
pc-dbg:
	cd sched/src && $(MAKE) lib
	cd stab/src && $(MAKE) lib
	$(CC) -c main.c -Isched/src
	$(CC) -o $(PROG) main.o $(GROUP_LIBS)


ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS)
ardu:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu


ardu: CC=avr-gcc
ardu: CFLAGS+=$(ARDUINO_FLAGS) $(DEBUG_FLAGS)
ardu:
	cd sched/src && $(MAKE) ardu
	cd stab/src && $(MAKE) ardu



clean:
	rm $(PROG) *.o
	cd sched/src && $(MAKE) clean
	cd stab/src && $(MAKE) clean

	

.PHONY: lib