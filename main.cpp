#include <stdio.h>

#include "color.h"
#include "run_code.h"

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf(RED("please set the input file name as a command line parameter\n"));
        return 0;
    }

    Run(argv[1]);

    return 0;
}
