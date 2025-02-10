
/***************************************************

IMPORTANT: DO NOT MODIFY THIS FILE UNLESS YOU *REALLY*  
           KNOW WHAT YOU ARE DOING.

           THIS FILE SHOULD ONLY BE USED FOR WRITING
           TEST MIPS ASSEMBLY PROGRAMS. DO NOT USE
           IT FOR IMPLEMENTING THE CPU.

***************************************************/


//I Instructions

#define ADDI_OPCODE (0x08)
#define ADDIU_OPCODE (0x09)
#define LW_OPCODE (0x23)
#define LH_OPCODE (0x21)
#define LHU_OPCODE (0x25)
#define LB_OPCODE (0x20)
#define LBU_OPCODE (0x24)
#define SW_OPCODE (0x2b)
#define SH_OPCODE (0x29)
#define SB_OPCODE (0x28)
#define LUI_OPCODE (0x0f)
#define ANDI_OPCODE (0x0c)
#define ORI_OPCODE (0x0d)
#define XORI_OPCODE (0x0e)
#define SLTI_OPCODE (0x0a)
#define SLTIU_OPCODE (0x0b)
#define BEQ_OPCODE (0x04)
#define BNE_OPCODE (0x05)


//I Instructions

//opcode (6) rs(5) rt(5) imm(48)
#define ADDI_INSTRUCTION(__rt, __rs, __C) (((uint64_t) ADDI_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define ADDIU_INSTRUCTION(__rt, __rs, __C) (((uint64_t) ADDIU_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define LW_INSTRUCTION(__rt, __rs, __C) (((uint64_t) LW_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define LH_INSTRUCTION(__rt, __rs, __C) (((uint64_t) LH_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define LHU_INSTRUCTION(__rt, __rs, __C) (((uint64_t) LHU_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define LB_INSTRUCTION(__rt, __rs, __C) (((uint64_t) LB_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define LBU_INSTRUCTION(__rt, __rs, __C) (((uint64_t) LBU_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define SW_INSTRUCTION(__rt, __rs, __C) (((uint64_t) SW_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define SH_INSTRUCTION(__rt, __rs, __C) (((uint64_t) SH_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define SB_INSTRUCTION(__rt, __rs, __C) (((uint64_t) SB_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) __(5) rt(5) imm(48)
#define LUI_INSTRUCTION(__rt,__C) (((uint64_t) LUI_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define ANDI_INSTRUCTION(__rt, __rs, __C) (((uint64_t) ANDI_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define ORI_INSTRUCTION(__rt, __rs, __C) (((uint64_t) ORI_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define XORI_INSTRUCTION(__rt, __rs, __C) (((uint64_t) XORI_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define SLTI_INSTRUCTION(__rt, __rs, __C) (((uint64_t) SLTI_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define SLTIU_INSTRUCTION(__rt, __rs, __C) (((uint64_t) SLTIU_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define BEQ_INSTRUCTION(__rt, __rs, __C) (((uint64_t) BEQ_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))

//opcode(6) rs(5) rt(5) imm(48)
#define BNE_INSTRUCTION(__rt, __rs, __C) (((uint64_t) BNE_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__C) & (((uint64_t) 0x1 << 48) - 1)))


//J Instructions

#define J_OPCODE (0x02)
#define JAL_OPCODE (0x03)


//opcode(6) unused(10) offset(48)
#define J_INSTRUCTION(__offset) (((uint64_t) J_OPCODE << 58) | ((__offset) & (((uint64_t) 1 << 48) - 1)))

//opcode(6) unused(10) offset(48)
#define JAL_INSTRUCTION(__offset) (((uint64_t) JAL_OPCODE << 58) | ((__offset) &  (((uint64_t) 1 << 48) - 1)))


//R Instructions

//Opcode for all R instructions is 0
#define R_INSTRUCTION_OPCODE (0x0)

//funct codes
#define ADD_FUNCT (0x20)
#define SUB_FUNCT (0x22)
#define MULT_FUNCT (0x18)
#define DIV_FUNCT (0x1a)
#define MOD_FUNCT (0x1b)
#define AND_FUNCT (0x24)
#define OR_FUNCT (0x25)
#define XOR_FUNCT (0x26)
#define NOR_FUNCT (0x27)
#define SLT_FUNCT (0x2A)
#define SLTU_FUNCT (0x2B)
#define SLL_FUNCT (0x00)
#define SLLV_FUNCT (0x04) 
#define SRL_FUNCT (0x02)
#define SRLV_FUNCT (0x06) 
#define SRAV_FUNCT (0x07) 
#define SRA_FUNCT (0x03)
#define JR_FUNCT (0x08)
#define JALR_FUNCT (0x09) 
#define SYSCALL_FUNCT (0x0c)

//opcode (6) 	rs (5) 	rt (5) 	rd (5) 	unused (31) shamt (6) funct (6)

//  ((R_INSTRUCTION_OPCODE << 58) | ((__rs) << 53) | ((__rt) << 48) | ((__rd) << 43) | ((__shamt) << 6) | FUNCT)

#define ADD_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | ADD_FUNCT)
#define ADDU_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | ADDU_FUNCT) 
#define SUB_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | SUB_FUNCT) 
#define SUBU_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | SUBU_FUNCT) 

#define MULT_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | MULT_FUNCT) 

#define MULTU_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | MULTU_FUNCT) 

#define DIV_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | DIV_FUNCT) 

#define MOD_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | MOD_FUNCT) 

#define AND_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | AND_FUNCT) 
#define OR_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | OR_FUNCT) 
#define XOR_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | XOR_FUNCT) 
#define NOR_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | NOR_FUNCT) 
#define SLT_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | SLT_FUNCT)
#define SLTU_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | SLTU_FUNCT)
#define SLL_INSTRUCTION(__rd,__rt,__shamt) (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | ((__shamt) << 6) | SLL_FUNCT)
#define SLLV_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | SLLV_FUNCT) 
#define SRL_INSTRUCTION(__rd,__rt,__shamt) (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | ((__shamt) << 6) | SRL_FUNCT)
#define SRLV_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | SRLV_FUNCT) 
#define SRA_INSTRUCTION(__rd,__rt,__shamt) (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | ((__shamt) << 6) | SRA_FUNCT)
#define SRAV_INSTRUCTION(__rd,__rs,__rt)  (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | ((uint64_t) (__rt) << 48) | ((uint64_t) (__rd) << 43) | SRAV_FUNCT) 
#define JR_INSTRUCTION(__rs) (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | JR_FUNCT)
#define JALR_INSTRUCTION(__rs) (((uint64_t) R_INSTRUCTION_OPCODE << 58) | ((uint64_t) (__rs) << 53) | JALR_FUNCT)


//Just the funct field
#define SYSCALL_INSTRUCTION SYSCALL_FUNCT
