#include <stdio.h>

#include "change_stack.h"
#include "color.h"
#include "dump.h"
#include "error_keys.h"
#include "SPU.h"

const size_t stack_capacity = 16;

ErrorKeys CtorSpu(SPU* spu)
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

    return NO_ERRORS;
}
