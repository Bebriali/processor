#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "change_stack.h"
#include "color.h"
#include "ex_commands.h"
#include "get_codeline.h"
#include "run_code.h"

typedef int CodeCell_t;

ErrorKeys GetCode(const char* filename, SPU* spu)
{
    assert(spu != NULL);

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

    getchar();

    printf("\n");

    return NO_ERRORS;
}


