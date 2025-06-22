#include "include/lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("[Main]: Please specify an input file. Usage: \"./.a.out input_file\"\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
