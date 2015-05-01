#ifndef STRUCT_TRANSACTION
#define STRUCT_TRANSACTION
struct BnkTransaction {
	char *Code;
	char *Date;
	char *Description;
	float Withdrawal;
	float Credit;
	int Checked;
};
#endif
