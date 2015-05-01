#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "transaction.h"
#include "CommandParser.h"

int main(int argc, char *argv[])
{
    printf("Welcome to Mikey's Checkbook\n\n");
    char *command_ret;
    command_ret = command();
    printf("Command: %s\n\n", command_ret);
    free(command_ret);
    return 0;
}
