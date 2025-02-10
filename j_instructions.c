#include <stdint.h>
#include "j_instructions.h"
#include "cpu.h"
#define OPCODE ((instruction >> 58) & 0x1F)
#define OFFSET (instruction & 0xFFFFFFFFFFFF)

uint64_t sign_extend_j(uint64_t value, int bits) {
    uint64_t mask = 1ULL << (bits - 1);
    if (value & mask) {
        value |= (0xFFFFFFFFFFFFFFFFULL << bits);
    }
    return value;
}

void j(uint64_t instruction) {
    int64_t extended_imm = sign_extend_j(OFFSET, 47);
    npc = (int64_t) ((pc + 8) + extended_imm);
}

void jal(uint64_t instruction) {
    registers[31] = (uint64_t) (pc + 8);
    int64_t extended_imm = sign_extend_j(OFFSET, 47);
    npc = (int64_t) ((pc + 8) + extended_imm);
}
