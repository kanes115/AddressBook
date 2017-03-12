all: LibAddressBook

LibAddressBook: LibAddressBook.o bintreeAddBook.o listAddBook.o
	gcc LibAddressBook.o bintreeAddBook.o listAddBook.o

LibAddressBook.o: LibAddressBook.c
	gcc -c LibAddressBook.c

bintreeAddBook.o: bintreeAddBook.c
	gcc -c bintreeAddBook.c

listAddBook.o: listAddBook.c
	gcc -c listAddBook.c

clean:
	rm *.o LibAddressBook
