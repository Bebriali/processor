#include <stdio.h>
#include <math.h>

#include "error_keys.h"
#include "dump.h"
#include "change_stack.h"
#include "color.h"
#include "commands_name.h"
#include "stack.h"
#include "debug_info.h"

ErrorKeys Push(Stack* stk, StackCell_t a)
{
    if (stk == NULL)
        return STK_ADDR;

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
    if (stk == NULL)
        return STK_ADDR;

    ErrorKeys code_error = NO_ERRORS;
    if ((code_error = StackPop(stk, a)) != NO_ERRORS)
    {
        printf("error in:\n file %s\n func %s\n line %d\n", __FILE__, __func__, __LINE__);
        printf("code_error = %d\n", code_error);
        return code_error;
    }
    ON_DEBUG(printf("a_addr = %p\n", a);)
    ON_DEBUG(printf("a_value = %lf\n", *a);)
    return NO_ERRORS;
}

ErrorKeys Multiply(Stack* stk)
{
    if (stk == NULL)
        return STK_ADDR;

    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, a * b);
}

ErrorKeys Add(Stack* stk)
{
    if (stk == NULL)
        return STK_ADDR;

    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, a + b);
}

ErrorKeys Div(Stack* stk)
{
    if (stk == NULL)
        return STK_ADDR;

    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, b / a);
}

ErrorKeys Subtract(Stack* stk)
{
    if (stk == NULL)
        return STK_ADDR;

    StackCell_t a = 0; StackPop(stk, &a);
    StackCell_t b = 0; StackPop(stk, &b);
    return Push(stk, b - a);
}

ErrorKeys GetValue(Stack* stk)
{
    if (stk == NULL)
        return STK_ADDR;

    printf(MAGENTA("Enter value : "));
    StackCell_t value = 0;
    scanf("%lf", &value);
    Push(stk, value);

    return NO_ERRORS;
}

ErrorKeys Out(Stack* stk)
{
    if (stk == NULL)
        return STK_ADDR;

    StackCell_t a = 0; StackPop(stk, &a);
    printf(MAGENTA("OUT : %lf\n"), a);
    return NO_ERRORS;
}

ErrorKeys Sqr(Stack* stk)
{
    if (stk == NULL)
        return STK_ADDR;

    StackCell_t a = 0; StackPop(stk, &a);

    StackPush(stk, sqrt(a));

    return NO_ERRORS;
}


ErrorKeys Halt(Stack* stk)
{
    DO_DUMP(stk);
    return StackDtor(stk);
}

bool Equal(Stack* stk)
{
    StackCell_t a = 0;
    StackPop(stk, &a);
    StackCell_t b = 0;
    StackPop(stk, &b);

    return (bool) FloatEqual(a, b);
}

bool Below(Stack* stk)
{
    StackCell_t a = 0;
    StackPop(stk, &a);
    StackCell_t b = 0;
    StackPop(stk, &b);

    return a > b;
}

bool Above(Stack* stk)
{
    StackCell_t a = 0;
    StackPop(stk, &a);
    StackCell_t b = 0;
    StackPop(stk, &b);

    return b > a;
}
