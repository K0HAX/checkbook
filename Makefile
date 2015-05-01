all:
	gcc -O2 -Wall -c -fpic -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient CommandParser.c -o CommandParser.o
	ar rcs libCommandParser.a CommandParser.o
	gcc book.c -L. -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lCommandParser -o book
	rm *.o *.a
