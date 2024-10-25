#include <stdio.h>

#include "color.h"
#include "run_code.h"
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
    ErrorKeys ctor_status = CtorSpu(&spu);
    if (ctor_status != NO_ERRORS)
    {
        printf(RED("error in SPU constructor\n"));
        return 0;
    }

    Run(argv[1], &spu);

    return 0;
}
