#include <stdio.h>

#include "color.h"
#include "commands_name.h"
#include "dump.h"
#include "ex_commands.h"
#include "run_code.h"
#include "SPU.h"
#include "stack.h"

ErrorKeys Compile(SPU* spu)
{
    bool running = true;

    while (running)
    {
        printf(YELLOW("code[%d] = %d\n"), spu->ip + 1, spu->code[spu->ip + 1]);
        switch (spu->code[spu->ip])
        {
            case PUSH:
                Push(&spu->stack, spu->code[++spu->ip]);
                spu->ip++;
                break;
            case POP:
                spu->ip++;
                break;
            case JMP:
                printf("jumping\n");
                printf("1code ip = %d\n", spu->ip);
                spu->ip += 1;
                spu->ip = spu->code[spu->ip];
                printf("2code ip = %d\n", spu->ip);
                break;
            case JB:
                break;
            case JE:
                break;
            case MUL:
                Multiply(&spu->stack);
                spu->ip++;
                break;
            case ADD:
                Add(&spu->stack);
                spu->ip++;
                break;
            case DIV:
                Div(&spu->stack);
                spu->ip++;
                break;
            case SUB:
                Subtract(&spu->stack);
                spu->ip++;
                break;
            case IN:
                GetValue(&spu->stack);
                spu->ip += 1;
                break;
            case OUT:
                Out(&spu->stack);
                spu->ip++;
                break;
            case HLT:
                Halt(&spu->stack);
                running = false;
                break;
            case STX_ERR:
                printf(RED("ERROR IN COMMAND : %d\n"), spu->code[spu->ip]);
                DO_DUMP(&spu->stack);
                Halt(&spu->stack);
                running = false;
                break;
            default:
                printf(RED("ERROR IN COMMAND : %d\n"), spu->code[spu->ip]);
                DO_DUMP(&spu->stack);
                Halt(&spu->stack);
                running = false;
                break;
        }
    }
    return NO_ERRORS;
}

