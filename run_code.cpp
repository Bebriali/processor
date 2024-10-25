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

ErrorKeys GetCode(const char* filename, SPU* spu)
{
    FileInf code_file = {.name = filename, .stream = NULL, .typestream = "rb", .size = 0};
    InitCodeFile(&code_file);

    fread(&spu->cur_code_size, sizeof(CodeCell_t), 1, code_file.stream);

    printf("len read = %d\n", spu->cur_code_size);

    spu->code = (CodeCell_t*) calloc(spu->cur_code_size, sizeof(CodeCell_t));
    if (spu->code == NULL)
    {
        printf(RED("error in code callocation\n"));
        return EX_ERRORS;
    }

    fread(spu->code, sizeof(CodeCell_t), spu->cur_code_size, code_file.stream);

    printf("read code: ");
    for (size_t i = 0; i < spu->cur_code_size; i++)
    {
        printf("%d ", spu->code[i]);
    }
    printf("\n");

    return NO_ERRORS;

    //*buf = (char*) calloc(code_file.size, sizeof(char));
    //if (*buf == NULL)
    //{
    //    printf("error in calloc:\n file %s\n line %d\n", __FILE__, __LINE__);
    //    return 0;
    //}

    ////if (GetBuffer(buf, &code_file) != NO_ERRORS)
    ////{
    ////    printf(RED("error in getting buffer\n"
    ////               "file: %s\n"
    ////               "func: %s\n"
    ////               "line: %d\n"),
    ////                __FILE__,
    ////                __func__,
    ////                __LINE__);
    ////}

    //printf("buf = %d\n", buf);
    //printf("*buf = %s\n", *buf);
    //printf("file_size = %d\n", code_file.size);
    //for (size_t i = 0; i < code_file.size; i++)
    //{
    //    printf("*buf[%d] = '%c'\n", i, *(*buf + i));
    //}

    //CodeCell_t cmd1 = 0, cmd2 = 0, cmd3 = 0;
    //sscanf(*buf, "%d %d %d", &cmd1, &cmd2, &cmd3);
    //printf(RED("CMD = %d, %d, %d\n"), cmd1, cmd2, cmd3);

    //size_t code_size = 1;
    //for (size_t i = 0; i < code_file.size; i++)
    //{
    //    if (isspace(*(*buf + i)) && i + 1 < code_file.size && isspace(*(*buf + i)) != '\0')
    //    {
    //        code_size++;
    //        *(*buf + i) = '\0';
    //        printf("code size = %d\n", code_size);
    //    }
    //}
}

ErrorKeys Run(const char* filename, SPU* spu)
{
    GetCode(filename, spu);

    //CodeCell_t cmd = 0;
    //printf("code_size = %d\n", spu->cur_code_size);
    //for (spu->ip = 0; spu->ip < spu->cur_code_size; spu->ip++)
    //{
    //    sscanf((char*)((char*)buf + 2 * spu->ip), "%d", &cmd);
    //    printf("cmd[%d] = %d\n", spu->ip, cmd);
    //    spu->code[spu->ip] = cmd;
    //}

    //printf(RED("WARNING:\n\n"
    //           "resultive code\n"));
    //for (spu->ip = 0; spu->ip < spu->cur_code_size; spu->ip++)
    //{
    //    printf(MAGENTA("\tcode[%d] = %d\n"), spu->ip, spu->code[spu->ip]);
    //}

    spu->ip = 0;
    ErrorKeys code_status = Compile(spu);
    if (code_status != NO_ERRORS)
    {
        printf(RED("error in executing commands\n"));
        return EXECUTOR_ERR;
    }

    // !!!dtor to main!!!

    return NO_ERRORS;
}


