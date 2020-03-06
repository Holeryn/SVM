/*
  ░░░░░░░░░░▀▀▀██████▄▄▄░░░░░░░░░░
  ░░░░░░░░░░░░░░░░░▀▀▀████▄░░░░░░░
  ░░░░░░░░░░▄███████▀░░░▀███▄░░░░░
  ░░░░░░░░▄███████▀░░░░░░░▀███▄░░░
  ░░░░░░▄████████░░░░░░░░░░░███▄░░
  ░░░░░██████████▄░░░░░░░░░░░███▌░
  ░░░░░▀█████▀░▀███▄░░░░░░░░░▐███░
  ░░░░░░░▀█▀░░░░░▀███▄░░░░░░░▐███░
  ░░░░░░░░░░░░░░░░░▀███▄░░░░░███▌░
  ░░░░▄██▄░░░░░░░░░░░▀███▄░░▐███░░
  ░░▄██████▄░░░░░░░░░░░▀███▄███░░░
  ░█████▀▀████▄▄░░░░░░░░▄█████░░░░
  ░████▀░░░▀▀█████▄▄▄▄█████████▄░░
  ░░▀▀░░░░░░░░░▀▀██████▀▀░░░▀▀██░░
*/

#include "virtual_machine.h"
#include "testprogram.h"

int
fetch(struct cpu *machine) {
  return program[machine->PC];
}

void
eval(int instr, bool * flag,struct cpu *machine) {
  #if IN_DEBUG < 0
  printf("%d\n",instr);
  #endif

  switch (instr) {
  case HLT:
    { // Terminate the program
      *flag = false;
      break;
    }
  case PUSH:
    { //Push a from the stack
      machine->SP++;
      machine->stack[machine->SP] = program[machine->PC+1];
      break;
    }
  case POP:
    { // Pop a value into the stack
      int val_popped = machine->stack[machine->SP-=1];
      break;
    }
  case ADDS:
    { // ADD the first two value on the stack
      int a,b;
      int result;

      // Check if the stack is major than 1
      if (machine->SP < 1) {
        error("SP to small, aborting...\n", ERROR);
      }

      a = machine->stack[machine->SP-=1];
      b = machine->stack[machine->SP-=1];
      result = b + a;
      machine->SP+=1;
      machine->stack[machine->SP] = result;

      break;
    }
  case MOV:
    { // Move a in register b
      // there can be a invalid istruction like MOV A (into what ?)
      // TODO : check this error
      machine->registers[program[machine->PC+=1]] = program[machine->PC+=1];

      break;
    }
  case LABEL:
    {
      // there can be more thene one label
      // TODO : implement a linked_list for saved SP
      machine->Saved_PC = machine->PC;
      break;
    }
  case CMP:
    {
      // there can be a invalid istruction like CMP A (whit what ?)
      // TODO : check this error
      if ((program[machine->PC + 1]) == machine->registers[program[machine->PC + 2]])
        machine->Branche_Registers[EQ] = true;
      else if ((program[machine->PC + 1]) < machine->registers[program[machine->PC + 2]])
        machine->Branche_Registers[LE] = true;
      else if ((program[machine->PC + 1]) > machine->registers[program[machine->PC + 2]])
        machine->Branche_Registers[GR] = true;

      machine->PC += 2;
      break;
    }
  case JE:
    {
      if (machine->Branche_Registers[EQ] == true) {
        machine->PC = machine->Saved_PC;
        machine->Branche_Registers[EQ] = false;
      }

      CLEAR_BRACHE_REGISTERS;

      break;
    }
  case JL:
    {
      if (machine->Branche_Registers[LE] == true) {
        machine->PC = machine->Saved_PC;
        machine->Branche_Registers[LE] = false;
      }

      CLEAR_BRACHE_REGISTERS;

      break;
    }
  case JG:
    {
      if (machine->Branche_Registers[GR] == true) {
        machine->PC = machine->Saved_PC;
        machine->Branche_Registers[GR] = false;
      }

      CLEAR_BRACHE_REGISTERS;

      break;
    }
  case JMP:
    {
      machine->PC = machine->Saved_PC;
      break;
    }
  case PRINT:
    {
      printf("%d\n", machine->registers[program[machine->PC+=1]]);
      break;
    }
  default:
    break;
  }
}

void
error(char * s, int type) {
  if (type == ERROR) {
    printf("\x1b[31m %s \x1b[0m \n", s);
    abort();
  } else if (type == WARNING) {
    printf("\x1b[33m %s \x1b[0m \n", s);
  }

  return;
}
