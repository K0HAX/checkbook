#include <mysql.h>
extern char *command();
extern int BookDeposit(MYSQL *con, char *Code, char *Date, char *Description, char *Amount, char *Checked);
extern int BookLogin(MYSQL *con);
