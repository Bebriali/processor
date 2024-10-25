#ifndef GET_CODELINE_H
#define GET_CODELINE_H

#include "error_keys.h"
#include "struct_file.h"

ErrorKeys InitCodeFile(FileInf* file);
ErrorKeys GetBuffer(char** buffer, FileInf* file);

#endif
