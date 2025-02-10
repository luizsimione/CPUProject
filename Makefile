
CC=gcc
CFLAGS= -arch x86_64

all:	cpu


cpu:	cpu.o r_instructions.o i_instructions.o j_instructions.o syscall.o utilities.o test_programs.o
		$(CC) $(CFLAGS) -o cpu cpu.o r_instructions.o i_instructions.o j_instructions.o syscall.o utilities.o test_programs.o

clean:
		rm cpu.o r_instructions.o i_instructions.o j_instructions.o syscall.o utilities.o test_programs.o


