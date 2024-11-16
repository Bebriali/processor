#include <stdio.h>
#include <assert.h>

#include "color.h"
#include "commands_name.h"
#include "debug_info.h"
#include "dump.h"
#include "ex_commands.h"
#include "run_code.h"
#include "SPU.h"
#include "stack.h"

ErrorKeys Execute(SPU* spu)
{
    assert(spu != NULL);
    bool running = true;

    while (running)
    {
        ON_DEBUG(DumpSpu(spu);)

        ON_DEBUG(printf(YELLOW("code[%d] = %d\n"), spu->ip, spu->code[spu->ip]);)
        switch (spu->code[spu->ip])
        {
            case PUSH:
                Push(&spu->stack, GetArgs(spu));
                spu->ip++;
                break;
            case POP:
            {
                spu->ip++;
                ON_DEBUG(printf("spu->ip = %d\n", spu->ip);)
                ON_DEBUG(printf("spu->code[spu->ip + 1] = %d\n", spu->code[spu->ip + 1]);)
                ON_DEBUG(printf("registers[code[ip + 1]] = %lf\n", spu->registers[spu->code[spu->ip + 1]]);)
                if (spu->code[spu->ip] & 2)
                {
                    ON_DEBUG(printf("type arg = %d\n", spu->code[spu->ip]);)
                    Pop(&spu->stack, (StackCell_t*)&(spu->registers[spu->code[++spu->ip]]));
                    ON_DEBUG(printf("registers_addr = %p\n", &(spu->registers[spu->code[spu->ip]]));)
                    ON_DEBUG(printf("resisters_value = %lf\n", spu->registers[spu->code[spu->ip]]);)
                }
                else
                {
                    StackCell_t a = (StackCell_t) spu->code[++spu->ip];
                    Pop(&spu->stack, &a);
                }
                //DumpSpu(spu);
                spu->ip++;

                break;
            }
            case JMP:
                ON_DEBUG(printf("jumping\n");)
                ON_DEBUG(printf("code ip = %d\n", spu->ip);)
                spu->ip = (size_t) GetArgs(spu);
                ON_DEBUG(printf("code ip = %d\n", spu->ip);)
                break;
            case JB:
                if (Below(&spu->stack))
                {
                    spu->ip = (size_t) GetArgs(spu);
                }
                else
                {
                    spu->ip += 3;
                }
                break;
            case JE:
                if (Equal(&spu->stack))
                {
                    spu->ip = (size_t) GetArgs(spu);
                }
                else
                {
                    spu->ip += 3;
                }
                break;
            case JA:
                if (Above(&spu->stack))
                {
                    spu->ip = (size_t) GetArgs(spu);
                }
                else
                {
                    spu->ip += 3;
                }
                break;
            case MUL:
                Multiply(&spu->stack);
                spu->ip += 2;
                break;
            case ADD:
                Add(&spu->stack);
                spu->ip += 2;
                break;
            case DIV:
                Div(&spu->stack);
                spu->ip += 2;
                break;
            case SUB:
                Subtract(&spu->stack);
                spu->ip += 2;
                break;
            case IN:
                GetValue(&spu->stack);
                spu->ip += 2;
                break;
            case OUT:
                Out(&spu->stack);
                spu->ip += 2;
                break;
            case SQR:
                Sqr(&spu->stack);
                spu->ip += 2;
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

StackCell_t GetArgs(SPU* spu)
{
    assert(spu != NULL);

    ON_DEBUG(int op_code = spu->code[spu->ip];)
    ON_DEBUG(printf(GREEN("op_code = %d\n"), op_code);)
    int arg_type = spu->code[++spu->ip];
    ON_DEBUG(printf(BLUE("arg_type = %d\n"), arg_type);)

    StackCell_t result = 0;
    ON_DEBUG(printf(RED("result = %d\n"), (int)result);)
    ON_DEBUG(printf(RED("|\n>\n|\n"));)

    if (arg_type & 1)
    {
        result = spu->code[++spu->ip];
        ON_DEBUG(printf(RED("result = %d\n"), (int)result);)
        ON_DEBUG(printf(RED("|\n>\n|\n"));)
    }
    else if (arg_type & 2)
    {
        result = spu->registers[spu->code[++spu->ip]];
        ON_DEBUG(printf(RED("result = %d\n"), (int)result);)
        ON_DEBUG(printf(RED("|\n>\n|\n"));)
    }
    else if (arg_type & 4)
    {
        result = spu->code[++spu->ip];
        ON_DEBUG(printf(RED("result = %d\n"), (int)result);)
        ON_DEBUG(printf(RED("|\n>\n|\n"));)
    }

    ON_DEBUG(DumpSpu(spu);)

    return result;
}

