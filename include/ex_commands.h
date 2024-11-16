#ifndef EX_COMMANDS_H
#define EX_COMMANDS_H

#include "error_keys.h"
#include "SPU.h"

ErrorKeys Execute(SPU* spu);
StackCell_t GetArgs(SPU* spu);

#endif
