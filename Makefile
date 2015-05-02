all:
	gcc -O2 -Wall -std=gnu99 -c -fpic `mysql_config --cflags --libs` CommandParser.c -o CommandParser.o
	ar rcs libCommandParser.a CommandParser.o
	gcc book.c -O2 -Wall -fpic -L. `mysql_config --cflags --libs` -lCommandParser -o book
	rm *.o *.a

asm:
	gcc -O2 -Wall -std=gnu99 -c -fpic `mysql_config --cflags --libs` CommandParser.c -o CommandParser.o
	gcc -S -O2 -Wall -std=gnu99 -c -fpic `mysql_config --cflags --libs` CommandParser.c -o CommandParser.s
	ar rcs libCommandParser.a CommandParser.o
	gcc book.c -O2 -Wall -fpic -L. `mysql_config --cflags --libs` -lCommandParser -o book
	gcc book.c -O2 -Wall -fpic -S -L. `mysql_config --cflags --libs` -lCommandParser -o book.s
	rm *.o *.a

clean:
	rm book
