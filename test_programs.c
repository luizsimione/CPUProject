
/***************************************************

IMPORTANT: DO NOT MODIFY THIS FILE UNLESS YOU *REALLY*  
           KNOW WHAT YOU ARE DOING.

***************************************************/

#include <stdio.h>
#include <stdint.h>

#include "cpu.h"
#include "register_names.h"

#include "utilities.h"

#include "programming.h"

void simple_test()
{
  int32_t code_addr = 0;
  uint64_t *code_segment = (uint64_t *) &(memory[CODE_STARTING_ADDRESS]);
  code_segment[code_addr++] = ADDI_INSTRUCTION(T0, ZERO, 20); // $T0 = 0 + 20
  code_segment[code_addr++] = ADD_INSTRUCTION(A0,T0,ZERO);   // $A0 = T0

  // SHOULD PRINT 20
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = $0 + 1, for print_long syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;
  
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 10); // $v0 = $0 + 10, for exit syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
}

//This MIPS assembly program adds the number from 1 to N
//using a loop.
void sum_loop()
{
  int32_t code_addr = 0;
  uint64_t *code_segment = (uint64_t *) &(memory[CODE_STARTING_ADDRESS]);
  code_segment[code_addr++] = ADDI_INSTRUCTION(T0, ZERO, 20); //$T0 = 0 + 20
  code_segment[code_addr++] = ADDI_INSTRUCTION(T1, ZERO, 0); // $T1 = 0

  // LOOP_TOP:
  code_segment[code_addr++] = BEQ_INSTRUCTION(T0, ZERO, (3 << 3)); // if ($T0==0) jump 3 8-byte instructions ahead of next one
  code_segment[code_addr++] = ADD_INSTRUCTION(T1,T1,T0);  // $T1 = $T1 + $T0
  code_segment[code_addr++] = ADDI_INSTRUCTION(T0,T0,-1);  // $T0 = $T0-1
  code_segment[code_addr++] = J_INSTRUCTION((uint64_t) -4 << 3); // jump back 4 instructions from next one

 DONE:
  code_segment[code_addr++] = ADD_INSTRUCTION(A0,ZERO,T1); // A0 = $T1, the result to print
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = $0 + 1, for print_int syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 10); // $v0 = $0 + 10, for exit syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
}


//This MIPS assembly program computes factorial(7) iteratively.

void fac_iter()
{
  int32_t code_addr = 0;
  uint64_t *code_segment = (uint64_t *) &(memory[CODE_STARTING_ADDRESS]);

  code_segment[code_addr++] = ADDI_INSTRUCTION(T0, ZERO, 7); // N: $T0 = 0 + 7
  code_segment[code_addr++] = ADDI_INSTRUCTION(T1, ZERO, 1); // Running product: $T1 = 1

  //LOOP_TOP:
  code_segment[code_addr++] = BEQ_INSTRUCTION(T0, ZERO, (3 << 3)); // if ($T0(N)==0) jump 3 instructions ahead of next one
  code_segment[code_addr++] = MULT_INSTRUCTION(T1,T1,T0); // $T1 = $T1 * $T0
  code_segment[code_addr++] = ADDI_INSTRUCTION(T0,T0,-1); //$T0 = $T0-1  (N--)
  code_segment[code_addr++] = J_INSTRUCTION((uint64_t) -4 << 3); //jump to instruction 4 back from next one

  //DONE:
  code_segment[code_addr++] = ADD_INSTRUCTION(A0,ZERO,T1); // A0 = $T1, the result to print
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = $0 + 1, for print_int syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 10); // $v0 = $0 + 10, for exit syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
}


/* This MIPS assembly program computes factorial iteratively. */

void fac_rec()
{
  int32_t code_addr = 0;
  uint64_t *code_segment = (uint64_t *) &(memory[CODE_STARTING_ADDRESS]);
  //put a jump to the main code here
  code_segment[code_addr++] = J_INSTRUCTION(/* MAIN */ 13 << 3);  //  jump to MAIN, starting at the 13th instruction after next one

  uint64_t fac_label = (uint64_t) CODE_STARTING_ADDRESS + (code_addr << 3); // the address of FAC in bytes
  //FAC:
  code_segment[code_addr++] = BNE_INSTRUCTION(A0, ZERO, (2 << 3)); // if (A0 != 0) jump to RECURSE (2 instructions after next one)
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1);  //  $V0 (the return value) = 1
  code_segment[code_addr++] = J_INSTRUCTION(/*DONE*/ 9 << 3);  //  jump to DONE (9 instructions after the next one)
 
  //RECURSE: 
  code_segment[code_addr++] = ADDI_INSTRUCTION(SP,SP,-16); //make room for two registers (16 bytes) on the stack
  code_segment[code_addr++] = SW_INSTRUCTION(RA,SP,8);  //store $ra at 8($SP)
  code_segment[code_addr++] = SW_INSTRUCTION(A0,SP,0);  //store $A0 at ($SP)
  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,A0,-1); // A0 = A0-1 , to pass N-1 as the argument 
  code_segment[code_addr++] = JAL_INSTRUCTION((uint64_t) -8 << 3);  //call FAC, XX instructions before next one
  code_segment[code_addr++] = LW_INSTRUCTION(A0,SP,0); //restore A0 from ($SP)
  code_segment[code_addr++] = LW_INSTRUCTION(RA,SP,8);  //restore $ra from 8($SP)
  code_segment[code_addr++] = ADDIU_INSTRUCTION(SP,SP,16); //adjust SP by 16
  code_segment[code_addr++] = MULT_INSTRUCTION(V0,V0,A0);  //multiply V0 (the return value from the recursive call) by A0 (N)

  //DONE:
  code_segment[code_addr++] = JR_INSTRUCTION(RA);  //  RETURN by jumping to the return address stored in $ra

  //MAIN:
  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,ZERO,6); // $A0 = 6, the initial value for N

  //Testing JALR to make a call, rather than JAL as above.
  code_segment[code_addr++] = LUI_INSTRUCTION(T4, fac_label >> 32); //put upper 32 bits of target address into top half of T4
  code_segment[code_addr++] = ORI_INSTRUCTION(T4,T4, fac_label & 0xFFFFFFFF); // put lower 32 bits of target address into bottom half of T4
  code_segment[code_addr++] = JALR_INSTRUCTION(T4); //call to the address in T4
    
  code_segment[code_addr++] = ADD_INSTRUCTION(A0,ZERO,V0); // $A0 = V0, the result to print
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = $0 + 1, for print_int syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 10); // $v0 = $0 + 10, for exit syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
}


//This is a general test of as many instructions (not tested by
//the other programs) as possible.

void instruction_test()
{
  int32_t code_addr = 0;
  uint64_t *code_segment = (uint64_t *) &(memory[CODE_STARTING_ADDRESS]);;
  uint64_t data_addr = DATA_STARTING_ADDRESS;
  data_addr += 50; //test using location other than the start of the data section
  //Testing LH and ORI
  uint64_t x_addr = data_addr;
  uint64_t *x_ptr = (uint64_t *) &(memory[data_addr]);
  data_addr += 4;  //made room for x

  *x_ptr = 0x110111011; // x = 4564520977

  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32

  // Loads x = 4564520977 into A0
  code_segment[code_addr++] = LW_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT 4564520977
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  //Loads bottom half of x, namely 0x10111011 = 269553681 into A0
  code_segment[code_addr++] = LH_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT 269553681
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing LB
  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  //Loads bottom byte of x, namely 0x11 = 17 into A0
  code_segment[code_addr++] = LB_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT 17
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing NOR, ANDI
  code_segment[code_addr++] = NOR_INSTRUCTION(T1,ZERO,ZERO);  //sets T1 to all 1's

  code_segment[code_addr++] = ANDI_INSTRUCTION(A0,T1,345);  //since T1 is all 1's, T0 = 345

  //This code prints the integer that is in A0
  //SHOULD PRINT 345
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  
  //Testing XORI (Note: A xor B xor A => B)
  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,ZERO,125);  //A0 = 125
  code_segment[code_addr++] = XORI_INSTRUCTION(A0,A0,99);  //A0 = A0 XOR 99
  code_segment[code_addr++] = XORI_INSTRUCTION(A0,A0,125);  //A0 = A0 XOR 125, should be 99

  //This code prints the integer that is in A0
  //SHOULD PRINT 99
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing SLL, by shifting A0 left by 2. If A0 contains 345, the result should be 1380
  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,ZERO,345);  //A0 = 345
  code_segment[code_addr++] = SLL_INSTRUCTION(A0, A0, 2);

  //This code prints the integer that is in A0
  //SHOULD PRINT 1380
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SRL, by shifting A0 right by 3. Since A0 contains 1380, the result should be 172
  code_segment[code_addr++] = SRL_INSTRUCTION(A0, A0, 3);

  //This code prints the integer that is in A0
  //SHOULD PRINT 172
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SUB, and SRA. Put -25 into A0 and shift right by 2. The result should be -7
  
  code_segment[code_addr++] = ADDI_INSTRUCTION(T2,ZERO, 25);
  code_segment[code_addr++] = SUB_INSTRUCTION(A0, ZERO, T2); //A0 = -25

  code_segment[code_addr++] = SRA_INSTRUCTION(A0, A0, 2); //Now A0 = -7 (rounds down)

  //This code prints the integer that is in A0
  //SHOULD PRINT -7
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SLLV
  code_segment[code_addr++] = ADDI_INSTRUCTION(A0, ZERO, 7); // A0 = 7
  code_segment[code_addr++] = ADDI_INSTRUCTION(T0, ZERO, 3); // T = 3, the shift amount

  // By shifting A0 left by T0 (3), since A0 contained 7, the result should be 56
  code_segment[code_addr++] = SLLV_INSTRUCTION(A0, A0, T0);

  //This code prints the integer that is in A0
  //SHOULD PRINT 56
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SRL, by shifting A0 right by 2. Since A0 contains 56, the result should be 14
  code_segment[code_addr++] = ADDI_INSTRUCTION(T0, ZERO, 2); // T = 2, the shift amount
  code_segment[code_addr++] = SRLV_INSTRUCTION(A0, A0, T0);

  //This code prints the integer that is in A0
  //SHOULD PRINT 14
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SUB, and SRAV. Put -25 into A0 and shift right by 2. The result should be -7
  
  code_segment[code_addr++] = ADDI_INSTRUCTION(T2,ZERO, 25);
  code_segment[code_addr++] = SUB_INSTRUCTION(A0, ZERO, T2); //A0 = -25

  code_segment[code_addr++] = SRAV_INSTRUCTION(A0, A0, T0); //Now A0 = -7 (rounds down)

  //This code prints the integer that is in A0
  //SHOULD PRINT -7

  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SH, writing 0x23456789 to low half-word of x
  //x should then be 0x123456789 = 4886718345 decimal
  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  code_segment[code_addr++] = ADDI_INSTRUCTION(T1, ZERO, 0x23456789);
  code_segment[code_addr++] = SH_INSTRUCTION(T1, T0, x_addr-DATA_STARTING_ADDRESS);

  //Now loading all of x and printing it.
  code_segment[code_addr++] = LW_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT 4886718345
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing SB, writing 0x00 to low byte of x (although the register will contain 0xff00)
  //x should then be 0x123456700 = 4886718208 decimal
  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  code_segment[code_addr++] = ADDI_INSTRUCTION(T1,ZERO, 0xff00);
  code_segment[code_addr++] = SB_INSTRUCTION(T1, T0, x_addr-DATA_STARTING_ADDRESS);

  //Now loading all of x and printing it.
  code_segment[code_addr++] = LW_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT 4886718208
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing LH and LHU.  Set x = 0x 0fff ffff ffff and perform LH and then LHU. LH should
  //load a negative number (-1), LHU should load a positive number (4294967295)

  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  code_segment[code_addr++] = ADDI_INSTRUCTION(T3,ZERO,(uint64_t) 0x0fffffffffff); // 44 ones (room for 48 bits)

  code_segment[code_addr++] = SW_INSTRUCTION(T3, T0, x_addr-DATA_STARTING_ADDRESS);

  code_segment[code_addr++] = LH_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT -1
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  code_segment[code_addr++] = LHU_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT 4294967295
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing LB and LBU.  Set x = 0x11ff and perform LB and then LBU. LB should
  //load a negative number (-1), LBU should load a positive number (255)

  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  code_segment[code_addr++] = ADDI_INSTRUCTION(T3,ZERO,0x11ff); 

  code_segment[code_addr++] = SW_INSTRUCTION(T3, T0, x_addr-DATA_STARTING_ADDRESS);

  code_segment[code_addr++] = LB_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT -1
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  code_segment[code_addr++] = LUI_INSTRUCTION(T0,DATA_STARTING_ADDRESS >> 32);  //loads top 32 bits
  code_segment[code_addr++] = ORI_INSTRUCTION(T0,T0,DATA_STARTING_ADDRESS & 0xFFFFFFFF);  //lower 32 bits

  code_segment[code_addr++] = LBU_INSTRUCTION(A0, T0, x_addr-DATA_STARTING_ADDRESS);

  //This code prints the integer that is in A0
  //SHOULD PRINT 255
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing LUI.  Load 2 into the upper half of A0, printing 2^33 = 8589934592

  code_segment[code_addr++] = LUI_INSTRUCTION(A0, 2);

  //This code prints the integer that is in A0
  //SHOULD PRINT 8589934592
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SLT.  Setting A0 = (T5 (-1) < T6(200)) = 1 

  code_segment[code_addr++] = ADDI_INSTRUCTION(T5, ZERO, 0xFFFFFFFFFFFF);  // set T5 = -1 (due to sign extension of the 48 ones)
  code_segment[code_addr++] = ORI_INSTRUCTION(T6, ZERO, 200);
  code_segment[code_addr++] = SLT_INSTRUCTION(A0, T5, T6);

  //This code prints the integer that is in A0
  //SHOULD PRINT 1
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Now reverse order of operands to SLT, should print 0

  code_segment[code_addr++] = SLT_INSTRUCTION(A0, T6, T5);

  //This code prints the integer that is in A0
  //SHOULD PRINT 0
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing SLTI.  Setting A0 = (T5 (-1) < 200) = 1 
  code_segment[code_addr++] = ADDI_INSTRUCTION(T5, ZERO, 0xFFFFFFFFFFFF);  // set T5 = -1 (due to sign extension of the 48 ones)
  code_segment[code_addr++] = SLTI_INSTRUCTION(A0, T5, 200);

  //This code prints the integer that is in A0
  //SHOULD PRINT 1
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SLTI.  Setting A0 = (T5 (-1) < -2) = 0
  code_segment[code_addr++] = ADDI_INSTRUCTION(T5, ZERO, 0xFFFFFFFFFFFF);  // set T5 = -1 (due to sign extension of the 48 ones)
  code_segment[code_addr++] = SLTI_INSTRUCTION(A0, T5,0xFFFFFFFFFFFE); 

  //This code prints the integer that is in A0
  //SHOULD PRINT 0
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing SLTIU.  Setting A0 = (T5 (-1) < 200) = 0  (because -1 is interpreted as a large positive number)

  code_segment[code_addr++] = ADDI_INSTRUCTION(T5, ZERO, 0xFFFFFFFFFFFF);  // set T5 = -1 (due to sign extension of the 48 ones)  
  code_segment[code_addr++] = SLTIU_INSTRUCTION(A0, T5, 200);

  //This code prints the integer that is in A0
  //SHOULD PRINT 0
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //Testing SLTIU.  Setting A0 = (T5 (200) < -1) = 1  (because -1 is interpreted as a large positive number)

  code_segment[code_addr++] = ADDI_INSTRUCTION(T5, ZERO, 200); //sets T5 = 200
  code_segment[code_addr++] = SLTIU_INSTRUCTION(A0, T5, 0xFFFFFFFFFFFF); // A0 = (200 < -1) =  1

  //This code prints the integer that is in A0
  //SHOULD PRINT 1
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   
  
  //Test MULT (with large result)

  code_segment[code_addr++] = ADDI_INSTRUCTION(T5, ZERO, 12345678); //sets T5 = 12345678
  code_segment[code_addr++] = ADDI_INSTRUCTION(T6, ZERO, -87654321); //sets T6 = -87654321
  code_segment[code_addr++] = MULT_INSTRUCTION(A0, T5, T6); // SET A0 = T5 * T6 = -1082152022374638

  //This code prints the integer that is in A0
  //Should print -1082152022374638
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   
  
  //Testing DIV

  code_segment[code_addr++] = ADDI_INSTRUCTION(T5, ZERO, 456787654321); //sets T5 = 456787654321
  code_segment[code_addr++] = ADDI_INSTRUCTION(T6, ZERO, -456); //sets T6 = -456
  code_segment[code_addr++] = DIV_INSTRUCTION(A0, T5, T6); // SET A0 = T5 / T6 = -1001727312

  //This code prints the integer that is in A0
  //Should print -1001727312
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   
  
  // Testing MOD
  // T5 still contains 456787654321 and T6 still contains -456
  // Set A0 = T5 MOD T6 = 49

  code_segment[code_addr++] = MOD_INSTRUCTION(A0, T5, T6); // SET A0 = T5 / T6 = -1001727312

  //This code prints the integer that is in A0
  //Should print 49
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   


  //Testing AND, OR, and XOR

  code_segment[code_addr++] = ADDI_INSTRUCTION(T1,ZERO, 0xff); //T1 = 0xff
  code_segment[code_addr++] = ADDI_INSTRUCTION(T2,ZERO, 0x34); //T2 = 0x34
  code_segment[code_addr++] = AND_INSTRUCTION(T1,T1, T2); //T1 = T1 & T2 = 0x34
  code_segment[code_addr++] = ADDI_INSTRUCTION(T2,ZERO, 0x70); //NOW T2 = 0x70
  code_segment[code_addr++] = OR_INSTRUCTION(T1,T1, T2); //T1 = T1 OR T2 = 0x74

  code_segment[code_addr++] = ADD_INSTRUCTION(A0,T1,ZERO); //A0 = T1 = 0x74 = 116 for printing

  //This code prints the integer that is in A0
  //SHOULD PRINT 116
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  code_segment[code_addr++] = ADDI_INSTRUCTION(T2,ZERO, 0xf); //NOW T2 = 0xf 

  code_segment[code_addr++] = XOR_INSTRUCTION(A0,T1,T2); //A0 = T1 ^ T2 = 0x74 ^ 0xf = 0x7n = 123

  //This code prints the integer that is in A0
  //SHOULD PRINT 123
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //---- EXIT ------
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 10); // $v0 = $0 + 10, for exit syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 

}


void syscall_test()
{
  int32_t code_addr = 0;
  uint64_t *code_segment = (uint64_t *) &(memory[CODE_STARTING_ADDRESS]);
  uint64_t data_addr = DATA_STARTING_ADDRESS;
  int32_t i;
    
  //print_string test
  unsigned char prompt[] = "Enter Number >";
  uint64_t prompt_num_label = data_addr;
  //copy string into memory at the beginning of the data section
  for(i=0; prompt[i] != 0; i++) {
    memory[data_addr++] = prompt[i];
  }
  memory[data_addr++] = 0;
  //Another prompt
  unsigned char prompt_str[] = "Enter String >";
  uint64_t prompt_str_label = data_addr;
  //copy string into memory at the beginning of the data section
  for(i=0; prompt_str[i] != 0; i++) {
    memory[data_addr++] = prompt_str[i];
  }
  memory[data_addr++] = 0;

  // Providing the address as an immediate is fine, since 48 bits is sufficient

  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,ZERO, prompt_num_label); // load A0 with address of prompt

  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 4); // $v0 = $0 + 4, for print_string syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 

  //read_int test
  
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 5); // $v0 = $0 + 5, for read_int, result is put in V0
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   
  code_segment[code_addr++] = ADD_INSTRUCTION(A0,ZERO,V0); //$a0 = $v0, getting ready call print_int
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 1); // $v0 = 1, for print_int,
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;   

  //printing string prompt

  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,ZERO, prompt_str_label); // load A0 with address of prompt

  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 4); // $v0 = $0 + 4, for print_string syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 

  //read_string test
  //read_string: $a0 = memory address of string input buffer
  //             $a1 = length of string buffer (n)       

#define STRING_BUF_SIZE 80
  uint64_t input_string_addr = data_addr; 
  data_addr += STRING_BUF_SIZE;
  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 8); // $v0 = $8, for read_int, 

  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,ZERO, input_string_addr); // load A0 with address of buff  

  code_segment[code_addr++] = ADDI_INSTRUCTION(A1, ZERO, STRING_BUF_SIZE); // $a1 = size of string buffer
  code_segment[code_addr++] = SYSCALL_INSTRUCTION;  

  //now print the string just read
  code_segment[code_addr++] = ADDI_INSTRUCTION(A0,ZERO, input_string_addr); // load A0 with address of buff    

  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 4); // $v0 = $0 + 4, for print_string syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 

  //exit

  code_segment[code_addr++] = ADDI_INSTRUCTION(V0, ZERO, 10); // $v0 = $0 + 10, for exit syscall.
  code_segment[code_addr++] = SYSCALL_INSTRUCTION; 
}



int main()
{

  cpu_initialize();
  simple_test();
  printf("Executing a very simple test of add and addi instructions\n");  
  cpu_execute();

  cpu_initialize();
  sum_loop();
  printf("Executing a program testing a simple loop\n");
  cpu_execute();

  cpu_initialize();
  fac_iter();
  printf("\nExecuting an iterative factorial program\n");
  cpu_execute();

  cpu_initialize();
  fac_rec();
  printf("\nExecuting a recursive factorial program\n");
  cpu_execute();
  
  cpu_initialize();
  syscall_test();
  printf("\nExecuting a program testing the syscall (I/O) function\n");
  cpu_execute();

  cpu_initialize();
  printf("\nExecuting a program testing all instructions not tested above\n");
  instruction_test();
  cpu_execute();

}
