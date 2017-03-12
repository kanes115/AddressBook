all:
	$(CC) -o libAddressBook LibAddressBook.c bintreeAddBook.c listAddBook.c -I.
