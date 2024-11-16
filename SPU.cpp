#include <stdio.h>

#include "change_stack.h"
#include "color.h"
#include "dump.h"
#include "error_keys.h"
#include "run_code.h"
#include "SPU.h"

const size_t stack_capacity = 16;

ErrorKeys CtorSpu(SPU* spu, const char* filename)
{
    ErrorKeys init_status = StackInit(&spu->stack, stack_capacity);
    if (init_status != NO_ERRORS)
    {
        DO_DUMP(&spu->stack);
        printf(RED("error in stack initialization\n"));
        return init_status;
    }


    spu->code = NULL;
    spu->cur_code_size = 0;
    spu->ip = 0;
    GetCode(filename, spu);

    return NO_ERRORS;
}

ErrorKeys DumpSpu(SPU* spu)
{
    if (spu != NULL && spu->code != NULL)
    {
        printf("code :\n");

        for (size_t i = spu->ip; i < spu->cur_code_size && i < spu->ip + 10; i++)
        {
            if(i == spu->ip)
            {
                printf(BLUE("%3d "), i);
            }
            else
            {
                printf("%3d ", i);
            }
        }
        printf("\n");

        for (size_t i = spu->ip; i < spu->cur_code_size && i < spu->ip + 10; i++)
        {
            if (i == spu->ip)
            {
                printf(BLUE("%3d"), spu->code[i]);
            }
            else
            {
                printf("%3d ", spu->code[i]);
            }
        }
        printf("\n");

        printf("registers :\n");

        printf(" AX BX CX DX ...\n");
        for (int i = 0; i < register_quantity; i++)
        {
            printf("%3lg", spu->registers[i]);
        }
        printf("\n");

        printf("stack :\n");
        printf(BLUE("stack cur_size = %d\n"), spu->stack.cur_size);
        for (size_t i = 0; i < spu->stack.cur_size; i++) printf("%3d " , i);
        printf("\n");
        for (size_t i = 0; i < spu->stack.cur_size; i++) printf("%3lg ", spu->stack.data[i]);
        printf("\n");
        printf("[press enter to continue] ");
        getchar();

        return NO_ERRORS;

    }

    return EX_ERRORS;
}
