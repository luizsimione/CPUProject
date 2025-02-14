
#define BOOL int
#define TRUE 1
#define FALSE 0

/* Word size */

#define WORD_SIZE_IN_BITS 64


/* The Registers */

#define NUM_REGISTERS 32

extern uint64_t registers[];

//pc holds the current value of the PC (program counter). 
//IMPORTANT: pc may be read by an instruction, but should not 
//be modified by an instruction.
extern uint64_t pc;  

//npc is the value that the PC will be assigned to once the current
//instruction is completed. A jump or branch instruction should modify
//the value of npc if the jump or branch is taken.  If an instruction
//does not assign a value to npc, it will be given the value of
//pc+8.  IMPORTANT: npc may be modified by an instruction (but only
//by jump or branch), but it should not be read by an instruction.
extern uint64_t npc;

//Memory is an array of bytes (not words).
extern uint8_t memory[];


/* Memory-related Constants */

#define MEMORY_SIZE_IN_BYTES (1 << 20)

#define CODE_STARTING_ADDRESS ((uint64_t) 100)
#define DATA_STARTING_ADDRESS ((uint64_t) 1 << 16)

#define STACK_STARTING_ADDRESS (MEMORY_SIZE_IN_BYTES - 8)  //highest full word address

// There are 8 bytes per word
#define CODE_STARTING_ADDRESS_IN_WORDS (CODE_STARTING_ADDRESS >> 3)

//This is the procedure for initializing (or reinitializing) the CPU.
void cpu_initialize();

//This is the procedure for causing the CPU to execute. It should
//start by executing the instruction at address CODE_STARTING_ADDRESS
void  cpu_execute();

//This procedure will cause the CPU to stop executing the current program. 
//If errorcode is 0, a message indicating normal termination will be printed. 
//Otherwise, a message indicating abnormal termination, along with the
//errorcode, will be printed.
void cpu_exit(int errorcode);
