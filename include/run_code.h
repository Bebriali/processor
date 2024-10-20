#ifndef RUN_CODE_H
#define RUN_CODE_H

ErrorKeys Multiply(Stack* stk);
ErrorKeys Add(Stack* stk);

ErrorKeys Div(Stack* stk);
ErrorKeys Subtract(Stack* stk);

ErrorKeys Out(Stack* stk);

ErrorKeys Halt(void);

#endif