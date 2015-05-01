#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mysql.h>
#include <termios.h>
#include <unistd.h>
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

char getpassch() {
    struct termios oldtc, newtc;
    char ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}

char *getPass()
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
        while ((c = getpassch() ) != '\n' && c != EOF)
        {
            pStr[i++]=(char)c;

            if(i == current_size)
            {
                current_size = i+len_max;
                pStr = realloc(pStr, current_size);
            }
        }
        printf("\n");
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
    
    command_password = getPass();

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

int BookDeposit(MYSQL *con)
{
    char *Code;
    char *Date;
    char *Description;
    char *Amount;
    char *Checked;
    printf("Code");
    Code = command();
    printf("Date (YYYY-MM-DD)");
    Date = command();
    printf("Description");
    Description = command();
    printf("Amount");
    Amount = command();
    printf("Checked (1 or 0)");
    Checked = command();

    char dst[256];
    dst[0] = '\0';
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
        free(Code);
        free(Date);
        free(Description);
        free(Amount);
        free(Checked);
        finish_with_error(con);
        return 1;
    } else {
        free(Code);
        free(Date);
        free(Description);
        free(Amount);
        free(Checked);
        return 0;
    }
}

int BookWithdrawal(MYSQL *con)
{
    char *Code;
    char *Date;
    char *Description;
    char *Amount;
    char *Checked;
    printf("Code");
    Code = command();
    printf("Date (YYYY-MM-DD)");
    Date = command();
    printf("Description");
    Description = command();
    printf("Amount");
    Amount = command();
    printf("Checked (1 or 0)");
    Checked = command();

    char dst[256];
    dst[0] = '\0';
    strcat(dst, "INSERT INTO Ledger (Code, Date, Description, Amount, Checked) VALUES ('");
    strcat(dst, Code);
    strcat(dst, "', '");
    strcat(dst, Date);
    strcat(dst, "', '");
    strcat(dst, Description);
    strcat(dst, "', '-");
    strcat(dst, Amount);
    strcat(dst, "', '");
    strcat(dst, Checked);
    strcat(dst, "');");

    if (mysql_query(con, dst)) {
        free(Code);
        free(Date);
        free(Description);
        free(Amount);
        free(Checked);
        finish_with_error(con);
        return 1;
    } else {
        free(Code);
        free(Date);
        free(Description);
        free(Amount);
        free(Checked);
        return 0;
    }
}

int BookRows(MYSQL *con)
{
    if (mysql_query(con, "SELECT * FROM Ledger"))
    {
        finish_with_error(con);
        return 1;
    }

    MYSQL_RES *result = mysql_store_result(con);

    if(result == NULL)
    {
        finish_with_error(con);
        return 1;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s | ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
    printf("\n");
    return 0;
}

int BookBalance(MYSQL *con)
{
    if (mysql_query(con, "SELECT sum(Amount) FROM Ledger"))
    {
        finish_with_error(con);
        return 1;
    }

    MYSQL_RES *result = mysql_store_result(con);

    if(result == NULL)
    {
        finish_with_error(con);
        return 1;
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("Balance: %s", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
    printf("\n");
    return 0;
}

