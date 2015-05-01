all:
	gcc -O2 -Wall -std=gnu11 -c -fpic -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient CommandParser.c -o CommandParser.o
	ar rcs libCommandParser.a CommandParser.o
	gcc book.c -O2 -Wall -fpic -L. -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lCommandParser -o book
	rm *.o *.a

asm:
	gcc -O2 -Wall -std=gnu11 -c -fpic -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient CommandParser.c -o CommandParser.o
	gcc -S -O2 -Wall -std=gnu11 -c -fpic -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient CommandParser.c -o CommandParser.s
	ar rcs libCommandParser.a CommandParser.o
	gcc book.c -O2 -Wall -fpic -L. -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lCommandParser -o book
	gcc book.c -O2 -Wall -fpic -S -L. -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lCommandParser -o book.s
	rm *.o *.a

clean:
	rm book
