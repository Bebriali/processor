#ifndef COMMANDS_NAME_H
#define COMMANDS_NAME_H

#include "error_keys.h"
#include "stack.h"
#include "SPU.h"

enum Commands
{
    PUSH = 0,
    POP = 1,
    JMP = 2,
    JB = 3,
    JE = 4,
    ADD = 5,
    MUL = 6,
    DIV = 7,
    IN = 8,
    OUT = 9,
    SUB = 10,
    HLT = -1,
    STX_ERR = 666
};

ErrorKeys Push(Stack* stk, StackCell_t a);
ErrorKeys Pop(Stack* stk, StackCell_t* a);

ErrorKeys Multiply(Stack* stk);
ErrorKeys Add(Stack* stk);

ErrorKeys Div(Stack* stk);
ErrorKeys Subtract(Stack* stk);

ErrorKeys GetValue(Stack* stk);
ErrorKeys Out(Stack* stk);

ErrorKeys Sqr(Stack* stk);

ErrorKeys Halt(Stack* stk);

bool Equal(Stack* stk);
bool Above(Stack* stk);
bool Below(Stack* stk);

#endif
