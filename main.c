#include <stdio.h>
typedef enum {
    R0,
    R1,
    R2,
    R3,
    R5,
    R6,
    R7,
    R8,
    PC,
    SP,
    Count

} registers;

int Registers[Count];

typedef enum {
    PUSH,
    POP,
    ADD,
    SUB,
    DIV,
    MUL,
    MOV,
    HALT
} instruction_Set;

const int instructions[] = {
        PUSH, 12,
        PUSH, 15,
        ADD,
        PUSH, 6,
        SUB,
        MOV,R3, 5,
        HALT
};

int pc_Pointer = 0;
int start = 1;
int stack_Ptr = -1;
int stack[1024];
void decode(int instruction) {
    switch(instruction) {
        case PUSH: {
            stack_Ptr++;
            stack[stack_Ptr] = instructions[++pc_Pointer];
            break;
        }
        case POP: {
            printf("%d\n", stack[stack_Ptr]);
            stack_Ptr--;
            break;
        }
        case ADD: {
            int x = stack[stack_Ptr--];
            int y = stack[stack_Ptr--];
            int total = x + y;
            stack_Ptr++;
            stack[stack_Ptr] = total;
            printf("%d\n", total);
            break;
        }
        case MUL: {
            int x = stack[stack_Ptr--];
            int y = stack[stack_Ptr--];
            int result = x * y;
            stack_Ptr++;
            stack[stack_Ptr] = result;
            printf("%d\n", result);
            break;
        }
        case SUB: {
            int x = stack[stack_Ptr--];
            int y = stack[stack_Ptr--];
            int total = x - y;
            stack_Ptr++;
            stack[stack_Ptr] = total;
            printf("%d\n", total);
            break;
        }

        case DIV: {
            int x = stack[stack_Ptr--];
            int y = stack[stack_Ptr--];
            int result = x/y; // truncation may occur;
            stack_Ptr++;
            stack[stack_Ptr] = result;
            printf("%d\n", result);
            break;
        }
        case MOV: {
            Registers[instructions[++pc_Pointer]] = instructions[++pc_Pointer];
            break;
        }
        case HALT: {
            start = 0;
            break;
        }
    };
}

int fetch(){
    return instructions[pc_Pointer];
}

int main() {
    while(start){
        int current_Instruction = fetch();
        decode(current_Instruction);
        pc_Pointer++;
    }
    return 0;
}
