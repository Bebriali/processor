#include <stdio.h>

#include "error_keys.h"
#include "dump.h"
#include "change_stack.h"
#include "color.h"
#include "commands_name.h"
#include "stack.h"

ErrorKeys Push(Stack* stk, StackCell_t a)
{
    ErrorKeys code_error = NO_ERRORS;
    if ((code_error = StackPush(stk, a)) != NO_ERRORS)
    {
        printf("error in:\n file %s\n func %s\n line %d\n", __FILE__, __func__, __LINE__);
        printf("code_error = %d", code_error);
        return code_error;
    }

    return NO_ERRORS;
}

ErrorKeys Pop(Stack* stk, StackCell_t* a)
{
    ErrorKeys code_error = NO_ERRORS;
    if ((code_error = StackPop(stk, a)) != NO_ERRORS)
    {
        printf("error in:\n file %s\n func %s\n line %d\n", __FILE__, __func__, __LINE__);
        printf("code_error = %d\n", code_error);
        return code_error;
    }
    return NO_ERRORS;
}

ErrorKeys Multiply(Stack* stk)
{
    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, a * b);
}

ErrorKeys Add(Stack* stk)
{
    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, a + b);
}

ErrorKeys Div(Stack* stk)
{
    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, b / a);
}

ErrorKeys Subtract(Stack* stk)
{
    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, b - a);
}

ErrorKeys Out(Stack* stk)
{
    StackCell_t a = 0; StackPop(stk, &a);
    printf(MAGENTA("OUT : %lf\n"), a);
    return NO_ERRORS;
}

ErrorKeys Halt(Stack* stk)
{
    DO_DUMP(stk);
    return StackDtor(stk);
}
