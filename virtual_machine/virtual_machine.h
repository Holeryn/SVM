#ifndef VIRUTAL_MACHINE
#define VIRTUAL_MACHINE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Branche flags registers
typedef enum {EQ,LE,GR,NUM_BR_FLAGS} BR_Flags;

// General purpose Registers
typedef enum {A,B,C,D,E,F,NUM_REGISTER} Registers;

struct cpu {
  int PC;
  int SP;
  int Saved_PC;
  int stack[256];
  int registers[NUM_REGISTER];
  bool Branche_Registers[NUM_BR_FLAGS];
};

/*
* ## Prototypes ##
*/
int fetch(struct cpu *machine);
void eval(int instr, bool *flag,struct cpu *machine);
void error(char * s, int type);


#define CLEAR_BRACHE_REGISTERS	machine->Branche_Registers[EQ] = false;  \
  machine->Branche_Registers[LE] = false;                                \
  machine->Branche_Registers[GR] = false;

// Macro for error function
#define ERROR	1
#define WARNING	0
/*
 * istruction set
 * a,b,... = Value
 * R = Register
 * L = Label
 */
typedef enum {
              PUSH, // PUSH a
              ADDS, // ADDS
              MOV,  // MOV a,R
              POP,	// POP
              CMP,	// CMP R,R
              JE,	// JE L (Jump if equal)
              JG,	// JG L (Jump if greater)
              JL,	// JL L (Jump il less)
              JMP,	// JMP L (Jump to L)
              LABEL,// Set label
              PRINT,// Print R
              HLT	// HLT
}IstructionSet;

#endif
