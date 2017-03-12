all: libAddressBook

libAddressBook: libAddressBook.o bintreeAddBook.o listAddBook.o
	gcc libAddressBook.o bintreeAddBook.o listAddBook.o

libAddressBook.o: libAddressBook.c
	gcc -c libAddressBook.c

bintreeAddBook.o: bintreeAddBook.c
	gcc -c bintreeAddBook.c

listAddBook.o: listAddBook.c
	gcc -c listAddBook.c

clean:
	rm *.o libAddressBook
