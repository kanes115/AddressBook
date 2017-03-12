CC = gcc

static:
	$(CC) test.c -L.. -lAddressBook -o test

shared:
	$(CC) test.c -L.. -Wl,-rpath=.. -lAddressBook -o test

clean:
	@echo Removing output files
	@rm test
