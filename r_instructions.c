#include <stdint.h>
#include "cpu.h"
#include "r_instructions.h"
#define RS ((instruction >> 53) & 0x1F)
#define RT ((instruction >> 48) & 0x1F)
#define RD ((instruction >> 43) & 0x1F)
#define SHAMT ((instruction >> 6) & 0x3F)

void add(uint64_t instruction) {
    registers[RD] =  (uint64_t)((int64_t)registers[RS] + (int64_t)registers[RT]);
}

void sub(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] - (int64_t)registers[RT]);
}

void mult(uint64_t instruction) {
     registers[RD] = (uint64_t)((int64_t)registers[RS] * (int64_t)registers[RT]);
 }
 
void div(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] / (int64_t)registers[RT]);
}
 
void mod(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] % (int64_t)registers[RT]);
}
 
void and(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] & (int64_t)registers[RT]);
}
 
void nor(uint64_t instruction) {
    registers[RD] = (uint64_t)(~((int64_t)registers[RS] | (int64_t)registers[RT]));
}
 
void or(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] | (int64_t)registers[RT]);
}
 
void xor(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] ^ (int64_t)registers[RT]);
}
 
void sll(uint64_t instruction) {
    registers[RD] = (registers[RT] << (uint8_t)SHAMT);
}
 
void sllv(uint64_t instruction) {
     registers[RD] = (uint64_t)((int64_t)registers[RS] << (int64_t)registers[RT]);
}
 
void srl(uint64_t instruction) {
    registers[RD] = (uint64_t)registers[RT] >> SHAMT;
    uint64_t sign_bit = (uint64_t)(registers[RT] >> 63) & 0x1;
    
    if (sign_bit) {
        uint64_t sign_mask = (uint64_t)((1ULL << SHAMT) - 1) << (64 - SHAMT);
        registers[RD] |= sign_mask;
    }
}
 
void sra(uint64_t instruction) {
    uint64_t sign_bit = (uint64_t)(registers[RT] >> 63) & 0x1;
    registers[RD] = (uint64_t)registers[RT] >> SHAMT;
    
    if (sign_bit) {
        uint64_t sign_mask = (uint64_t)((1ULL << SHAMT) - 1) << (64 - SHAMT);
        registers[RD] |= sign_mask;
    }
}
 
void srlv(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] >> (int64_t)registers[RT]);
}
 
void srav(uint64_t instruction) {
    registers[RD] = (uint64_t)((int64_t)registers[RS] >> (int64_t)registers[RT]);
}
 
void slt(uint64_t instruction) {
    if ((int64_t)registers[RS] < (int64_t)registers[RT]) {
        registers[RD] = 1;
    } else {
        registers[RD] = 0;
    }
 }
 
void sltu(uint64_t instruction) {
    if ((int64_t)registers[RS] < (int64_t)registers[RT]) {
        registers[RD] = 1;
    } else {
        registers[RD] = 0;
    }
}
 
void jr(uint64_t instruction) {
    npc = (int64_t)registers[RS];
}
 
void jalr(uint64_t instruction) {
    registers[31] = (int64_t) (pc + 8);
    npc = (int64_t)registers[RS];
}
 
//void syscall(uint64_t instruction) {
//}
