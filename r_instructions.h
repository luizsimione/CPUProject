
//These are the R-instructions implemented by the simulted MIPS processor

void add(uint64_t instruction);

void sub(uint64_t instruction); 

void mult(uint64_t instruction); 

void div(uint64_t instruction); 

void mod(uint64_t instruction); 

void and(uint64_t instruction); 

void nor(uint64_t instruction); 

void or(uint64_t instruction); 

void xor(uint64_t instruction); 

void sll(uint64_t instruction); 

void sllv(uint64_t instruction); 

void srl(uint64_t instruction); 

void sra(uint64_t instruction); 

void srlv(uint64_t instruction); 

void srav(uint64_t instruction); 

void slt(uint64_t instruction); 

void sltu(uint64_t instruction); 

void jr(uint64_t instruction); 

void jalr(uint64_t instruction); 

void syscall(uint64_t instruction);  //This is actually defined in syscall.c
