#pragma once
#undef DEVICE_
#define DEVICE_ Core
#define VERSION_ 0
#define WORD_ 2
#include "devices.h"

#define ISA_STORE 0
#define ISA_LOAD 1 
#define ISA_SEND 2
#define ISA_RECV 3
#define ISA_WORD 4
#define ISA_HALT 5
#define ISA_JUMP 6
#define ISA_JZER 7
#define ISA_JNOZ 8
#define ISA_JEQU 9
#define ISA_JNEQ 10
#define ISA_PUSH 11
#define ISA_POP 12
#define ISA_CALL 13
#define ISA_MMRY 14
#define ISA_LDIM 15
#define ISA_JLTA 16
#define ISA_JLTB 17
#define ISA_ADDI 18
#define ISA_ADDR 19
#define ISA_SUBI 20
#define ISA_SUBR 21
#define ISA_MULI 22
#define ISA_MULR 23
#define ISA_DIVI 24
#define ISA_DIVR 25
#define ISA_FLAG 26
#define ISA_LSFT 27
#define ISA_RSFT 28


typedef struct {
    uint16_t registers[4]; // A B SP PC
    uint16_t cachedIDs;
    uint16_t stack[512];
    uint32_t InstructionRom[512];
    unsigned long long counter;
    uint64_t state;
} CoreData;
/*
LDIM A 'h'
LDIM B 0
STORE
ADDI B 1
LDIM A 'i'
STORE
LDIM A , 0
ADDI B 1
STORE 
SEND 1
;or 
LDIM S 0
LDIM A 'h'
PUSH A
LDIM A 'i'
PUSH A
LDIM A 0
PUSH A
or if you want something fancy
LDIM B 0
LDIM A 5
BUFF A
POP A ; self->DID
SEND A
POP A ; cachedIDs[0] //memory
SEND A
SEND B // address
LDIM A 'h' // CONTENT
SEND A
LDIM A 1
SEND A
*/
Device* NewBaseCore(const char* config);
Status CreateCore(Device* self , State* state);
Status ClockCore(Device* self, State* state);
Status DestroyCore(Device* self, State* state);