#ifndef RUN_CODE_H
#define RUN_CODE_H

#include "error_keys.h"

typedef int CodeCell_t;

size_t GetCode(const char* filename, char** buf);
ErrorKeys Run(const char* filename);

#endif
