#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mysql.h>
#include "transaction.h"
#include "CommandParser.h"

int main(int argc, char *argv[])
{
    MYSQL *con = mysql_init(NULL);
    printf("Welcome to Mikey's Checkbook\n\n");
    char *command_ret;
    int quit = 1;
    while(quit)
    {
        command_ret = command();
        printf("Command: %s\n\n", command_ret);
        if(strcmp(command_ret, "quit") == 0)
        {
            quit = 0;
        }
        if(strcmp(command_ret, "q") == 0)
        {
            quit = 0;
        }

        if(strcmp(command_ret, "login") == 0)
        {
            BookLogin(con);
            printf("Logged in.\n");
        }
        if(strcmp(command_ret, "l") == 0)
        {
            BookLogin(con);
            printf("Logged in.\n");
        }

        if(strcmp(command_ret, "deposit") == 0)
        {
            BookDeposit(con);
            printf("Done\n");
        }
        if(strcmp(command_ret, "d") == 0)
        {
            BookDeposit(con);
            printf("Done\n");
        }

        if(strcmp(command_ret, "withdrawal") == 0)
        {
            BookWithdrawal(con);
            printf("Done\n");
        }
        if(strcmp(command_ret, "w") == 0)
        {
            BookWithdrawal(con);
            printf("Done\n");
        }

        free(command_ret);
    }
    return 0;
}
