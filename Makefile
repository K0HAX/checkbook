all:
	gcc -O2 -Wall -c -fpic CommandParser.c -o CommandParser.o
	ar rcs libCommandParser.a CommandParser.o
	gcc book.c -L. -lCommandParser -o book
