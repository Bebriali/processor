#ifndef SPU_H
#define SPU_H

#include "error_keys.h"
#include "stack.h"
typedef int CodeCell_t;

const int register_quantity = 6;

struct SPU
{
    CodeCell_t* code;
    size_t cur_code_size;
    size_t ip;
    CodeCell_t registers[register_quantity];
    Stack stack;
};

ErrorKeys CtorSpu(SPU* spu);

#endif
