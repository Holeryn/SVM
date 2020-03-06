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


#include <stdio.h>
#include <unistd.h>

#include "virtual_machine.h"

/*
	-1 : istructions
    0  : normal
    1  : registers and flags
    2  : step by step
 */
#define IN_DEBUG 0


int
main(void) {
  //int curr_istruction;
  bool running = true;

  struct cpu *machine;
  machine->SP = -1;


  //Iterate the program
  for (machine->PC = 0; running ; machine->PC++) {
    #if IN_DEBUG > 0
    int i;

    printf("Pid = %ld\n",(long)getpid());
    printf("PC = %d\nSP = %d\n",PC, SP);

    for(i = 0; i < NUM_REGISTER; i++)
      printf("%d,",registers[i]);

    printf("\n");

    for(i = 0; i < NUM_BR_FLAGS; i++)
      printf("%d,",Branche_Registers[i]);

    printf("\n");

    #if IN_DEBUG == 2
    char c;
    scanf("%c",&c);
    #endif

    #endif
    eval(fetch(machine), &running,machine);
  }

  return 0;
}
