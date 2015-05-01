#include <mysql.h>
extern char *command();
extern int BookDeposit(MYSQL *con);
extern int BookWithdrawal(MYSQL *con);
extern int BookLogin(MYSQL *con);
extern int BookRows(MYSQL *con);
extern int BookBalance(MYSQL *con);
