#include <stdio.h>

#include "color.h"
#include "run_code.h"
#include "ex_commands.h"
#include "SPU.h"

typedef int CodeCell_t;

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf(RED("please set the input file name as a command line parameter\n"));
        return 0;
    }

    struct SPU spu = {};
    ErrorKeys ctor_status = CtorSpu(&spu, argv[1]);
    if (ctor_status != NO_ERRORS)
    {
        printf(RED("error in SPU constructor\n"));
        return 0;
    }

    ErrorKeys code_status = Execute(&spu);
    if (code_status != NO_ERRORS)
    {
        printf(RED("error in executing commands\n"));
        return EXECUTOR_ERR;
    }

    return 0;
}
