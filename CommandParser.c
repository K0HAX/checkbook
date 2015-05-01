#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mysql.h>
#include "transaction.h"

char *command()
{
    unsigned int len_max = 12;
    unsigned int current_size = 0;

    char *pStr = malloc(len_max);
    current_size = len_max;

    printf(">");

    if(pStr != NULL)
    {
        int c = EOF;
        unsigned int i = 0;
        while ((c = getchar() ) != '\n' && c != EOF)
        {
            pStr[i++]=(char)c;

            if(i == current_size)
            {
                current_size = i+len_max;
                pStr = realloc(pStr, current_size);
            }
        }
        pStr[i] = '\0';
        return pStr;
    }
    return NULL;
}

void finish_with_error(MYSQL *con)
{
        fprintf(stderr, "%s\n", mysql_error(con));
            mysql_close(con);
                exit(1);
}

int BookLogin(MYSQL *con)
{
    char *command_username;
    char *command_password;
    char *command_hostname;
    char *command_database;
    printf("username");
    command_username = command();
    printf("password");
    command_password = command();
    printf("hostname");
    command_hostname = command();
    printf("database");
    command_database = command();

    if (mysql_real_connect(con, command_hostname, command_username, command_password, command_database, 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
        free(command_username);
        free(command_password);
        free(command_hostname);
        free(command_database);
        return 1;
    } else {
        free(command_username);
        free(command_password);
        free(command_hostname);
        free(command_database);
        return 0;
    }
}

int BookDeposit(MYSQL *con, char *Code, char *Date, char *Description, char *Amount, char *Checked)
{
    char dst[256];
    strcat(dst, "INSERT INTO Ledger (Code, Date, Description, Amount, Checked) VALUES ('");
    strcat(dst, Code);
    strcat(dst, "', '");
    strcat(dst, Date);
    strcat(dst, "', '");
    strcat(dst, Description);
    strcat(dst, "', '");
    strcat(dst, Amount);
    strcat(dst, "', '");
    strcat(dst, Checked);
    strcat(dst, "');");

    if (mysql_query(con, dst)) {
        finish_with_error(con);
        return 1;
    } else {
        return 0;
    }
}
