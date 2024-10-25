#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "change_stack.h"
#include "color.h"
#include "error_keys.h"
#include "ex_commands.h"
#include "get_codeline.h"
#include "run_code.h"
#include "SPU.h"
#include "struct_file.h"

typedef int CodeCell_t;

size_t GetCode(const char* filename, char** buf)
{
    FileInf code_file = {.name = filename, .stream = NULL, .typestream = "rb", .size = 0};
    InitCodeFile(&code_file);

    *buf = (char*) calloc(code_file.size, sizeof(char));
    if (*buf == NULL)
    {
        printf("error in calloc:\n file %s\n line %d\n", __FILE__, __LINE__);
        return 0;
    }

    if (GetBuffer(buf, &code_file) != NO_ERRORS)
    {
        printf(RED("error in getting buffer\n"
                   "file: %s\n"
                   "func: %s\n"
                   "line: %d\n"),
                    __FILE__,
                    __func__,
                    __LINE__);
    }

    size_t code_size = 1;
    printf("code_size = %d\n", code_size);
    //printf("buf = %d\n", buf);
    printf("*buf = %s\n", *buf);
    printf("file_size = %d\n", code_file.size);
    for (size_t i = 0; i < code_file.size; i++)
    {
        printf("*buf[%d] = '%c'\n", i, *(*buf + i));
    }

    CodeCell_t cmd1 = 0, cmd2 = 0, cmd3 = 0;
    sscanf(*buf, "%d %d %d", &cmd1, &cmd2, &cmd3);
    printf(RED("CMD = %d, %d, %d\n"), cmd1, cmd2, cmd3);

    for (size_t i = 0; i < code_file.size; i++)
    {
        if (isspace(*(*buf + i)) && i + 1 < code_file.size && isspace(*(*buf + i)) != '\0')
        {
            code_size++;
            *(*buf + i) = '\0';
            printf("code size = %d\n", code_size);
        }
    }

    return code_size;
}

ErrorKeys Run(const char* filename)
{
    printf("i am running your code\n");

    struct SPU spu = {};
    ErrorKeys ctor_status = CtorSpu(&spu);
    if (ctor_status != NO_ERRORS)
    {
        printf(RED("error in SPU constructor\n"));
        return ctor_status;
    }

    char* buf = NULL;
    spu.cur_code_size = GetCode(filename, &buf);

    printf(BLUE("buffer = %s\n"), buf);

    CodeCell_t cmd = 0;
    spu.code = (CodeCell_t*) calloc(spu.cur_code_size, sizeof(CodeCell_t));
    printf("code_size = %d\n", spu.cur_code_size);
    for (spu.ip = 0; spu.ip < spu.cur_code_size; spu.ip++)
    {
        sscanf((char*)((char*)buf + 2 * spu.ip), "%d", &cmd);
        printf("cmd[%d] = %d\n", spu.ip, cmd);
        spu.code[spu.ip] = cmd;
    }

    printf(RED("WARNING:\n\n"
               "resultive code\n"));
    for (spu.ip = 0; spu.ip < spu.cur_code_size; spu.ip++)
    {
        printf(MAGENTA("\tcode[%d] = %d\n"), spu.ip, spu.code[spu.ip]);
    }

    spu.ip = 0;

    ErrorKeys code_status = Compile(&spu);
    if (code_status != NO_ERRORS)
    {
        printf(RED("error in executing commands\n"));
        return EXECUTOR_ERR;
    }

    return NO_ERRORS;
}


