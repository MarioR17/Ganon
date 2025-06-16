#include "include/gn.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Please specify input file.\n");
        return 1;
    }

    gn_compile(argv[1]);

    return 0;
}
