#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "cpu.h"
#include "i_instructions.h"

#define RS(instruction) (((instruction) >> 53) & 0x1F)
#define RT(instruction) (((instruction) >> 48) & 0x1F)
#define IMM(instruction) ((instruction) & 0x0000FFFFFFFFFFFF)

uint64_t sign_extend(uint64_t value, int bits) {
    uint64_t mask = 1ULL << (bits - 1);
    if (value & mask) {
        value |= (0xFFFFFFFFFFFFFFFFULL << bits);
    }
    return value;
}

void addi(uint64_t instruction) {
    registers[RT(instruction)] = (uint64_t)((int64_t)registers[RS(instruction)] + (int64_t)sign_extend(IMM(instruction), 48));
}

void addiu(uint64_t instruction) {
    registers[RT(instruction)] = registers[RS(instruction)] + IMM(instruction);
}

void lw(uint64_t instruction) {
    registers[RT(instruction)] = *((uint64_t *)&memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)]);
}

void lh(uint64_t instruction) {
    registers[RT(instruction)] = sign_extend(*((uint32_t *)&memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)]), 32);  
}

void lhu(uint64_t instruction) { 
    registers[RT(instruction)] = *((uint32_t *)&memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)]); 
}

void lb(uint64_t instruction) {
    registers[RT(instruction)] = sign_extend(memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)], 8);
}

void lbu(uint64_t instruction) {
    registers[RT(instruction)] = memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)];
}

void sw(uint64_t instruction) {
    *((uint64_t *)&memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)]) = registers[RT(instruction)];
}

void sh(uint64_t instruction) {
    *((uint32_t *)&memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)]) = registers[RT(instruction)]; 
}

void sb(uint64_t instruction) {
    memory[registers[RS(instruction)] + sign_extend(IMM(instruction), 48)] = registers[RT(instruction)];
}

void lui(uint64_t instruction) {
    registers[RT(instruction)] = IMM(instruction) << 32;
}

void ori(uint64_t instruction) {
    registers[RT(instruction)] = registers[RS(instruction)] | IMM(instruction);
}

void andi(uint64_t instruction) {
    registers[RT(instruction)] = registers[RS(instruction)] & IMM(instruction);
}

void xori(uint64_t instruction) {
    registers[RT(instruction)] = registers[RS(instruction)] ^ IMM(instruction);
}

void slti(uint64_t instruction) {
    registers[RT(instruction)] = ((int64_t)registers[RS(instruction)] < (int64_t)sign_extend(IMM(instruction), 48)) ? 1 : 0;
}

void sltiu(uint64_t instruction) {
    registers[RT(instruction)] = (registers[RS(instruction)] < sign_extend(IMM(instruction), 48)) ? 1 : 0;
}

void beq(uint64_t instruction) {
    if (registers[RS(instruction)] == registers[RT(instruction)]) {
        npc = pc + 8 + sign_extend(IMM(instruction), 48);
    }
}

void bne(uint64_t instruction) {  
    if (registers[RS(instruction)] != registers[RT(instruction)]) {
        npc = pc + 8 + sign_extend(IMM(instruction), 48);
    }
}
