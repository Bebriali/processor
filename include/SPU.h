#ifndef SPU_H
#define SPU_H

#include "error_keys.h"
#include "run_code.h"
#include "stack.h"

const int label_quantity = 15;
const int register_quantity = 6;

struct SPU
{
    CodeCell_t labels [label_quantity];
    CodeCell_t* code;
    size_t cur_code_size;
    size_t ip;
    CodeCell_t registers[register_quantity];
    Stack stack;
};

ErrorKeys CtorSpu(SPU* spu);

#endif
