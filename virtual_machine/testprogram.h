#ifndef TEST_PROGRAM
#define TEST_PROGRAM

const int program[] = {
                       MOV,3,A,
                       LABEL,
                       PRINT,A,
                       CMP,3,A,
                       JE,
                       PUSH,5,
                       PUSH,7,
                       ADDS,
                       POP,
                       HLT
};

#endif
