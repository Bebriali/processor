#include <stdio.h>
#include "run_code.h"

ErrorKeys Multiply(Stack* stk)
{
    StackCell_t a = StackPop(stk);
    StackCell_t b = StackPop(stk);
    return a * b;
}

ErrorKeys Add(Stack* stk)
{
    StackCell_t a = StackPop(stk);
    StackCell_t b = StackPop(stk);
    return a + b;
}

ErrorKeys Div(Stack* stk)
{
    StackCell_t a = StackPop(stk);
    StackCell_t b = STackPop(stk);
    return b / a;
}

ErrorKeys Subtract(Stack* stk)
{  
    StackCell_t a = StackPop(stk);
    StackCell_t b = STackPop(stk);
    return b - a;
}

ErrorKeys Out(Stack* stk)
{
    return StackPop(stk);
}

ErrorKeys Halt()
{
    
}