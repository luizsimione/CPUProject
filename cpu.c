#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "r_instructions.h"
#include "i_instructions.h"
#include "j_instructions.h"

uint64_t registers[NUM_REGISTERS];
uint64_t pc;
uint64_t npc;
uint8_t memory[MEMORY_SIZE_IN_BYTES];

#define OPCODE(instruction) ((instruction >> 58) & 0x3F)

void (*r_dispatch_table[64])(uint64_t);
void (*ij_dispatch_table[64])(uint64_t);
int running = 1;

void cpu_initialize() {
    running = 1;
    pc = CODE_STARTING_ADDRESS;
    npc = CODE_STARTING_ADDRESS;
    registers[29] = STACK_STARTING_ADDRESS;
    registers[0] = 0;

    r_dispatch_table[0x20] = &add;
    r_dispatch_table[0x22] = &sub;
    r_dispatch_table[0x18] = &mult;
    r_dispatch_table[0x1a] = &div;
    r_dispatch_table[0x1b] = &mod;
    r_dispatch_table[0x24] = &and;
    r_dispatch_table[0x25] = &or;
    r_dispatch_table[0x26] = &xor;
    r_dispatch_table[0x27] = &nor;
    r_dispatch_table[0x2a] = &slt;
    r_dispatch_table[0x2b] = &sltu;
    r_dispatch_table[0x00] = &sll;
    r_dispatch_table[0x04] = &sllv;
    r_dispatch_table[0x02] = &srl;
    r_dispatch_table[0x06] = &srlv;
    r_dispatch_table[0x03] = &sra;
    r_dispatch_table[0x07] = &srav;
    r_dispatch_table[0x08] = &jr;
    r_dispatch_table[0x09] = &jalr;
    r_dispatch_table[0x0c] = &syscall;

    ij_dispatch_table[0x08] = &addi;
    ij_dispatch_table[0x09] = &addiu;
    ij_dispatch_table[0x23] = &lw;
    ij_dispatch_table[0x21] = &lh;
    ij_dispatch_table[0x25] = &lhu;
    ij_dispatch_table[0x20] = &lb;
    ij_dispatch_table[0x24] = &lbu;
    ij_dispatch_table[0x2b] = &sw;
    ij_dispatch_table[0x29] = &sh;
    ij_dispatch_table[0x28] = &sb;
    ij_dispatch_table[0x0f] = &lui;
    ij_dispatch_table[0x0d] = &ori;
    ij_dispatch_table[0x0c] = &andi;
    ij_dispatch_table[0x0e] = &xori;
    ij_dispatch_table[0x0a] = &slti;
    ij_dispatch_table[0x0b] = &sltiu;
    ij_dispatch_table[0x04] = &beq;
    ij_dispatch_table[0x05] = &bne;
    ij_dispatch_table[0x02] = &j;
    ij_dispatch_table[0x03] = &jal;
}

void cpu_execute() {
    while (running) {
        pc = npc;
        npc += 8;
        uint64_t instruction = *((uint64_t *)&memory[pc]);
        uint8_t opcode = OPCODE(instruction);

        if (opcode == 0) {
            uint8_t funct = instruction & 0x3F;
            r_dispatch_table[funct](instruction);
        } else {
            ij_dispatch_table[opcode](instruction);
        }
    }
}

void cpu_exit(int errorcode) {
    if (errorcode == 0) {
        printf("\nProgram terminated normally.\n");
    } else {
        printf("Program terminated with error code: %d\n", errorcode);
    }
    running = 0;
}
