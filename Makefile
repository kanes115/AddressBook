CC = gcc
SHARED_OPTS = -c -fPIC
ARCHIVE = ar rcs

static: LibAddressBook_st

shared: LibAddressBook_so


#Static library:
LibAddressBook_st: bintreeAddBook.o listAddBook.o
	$(ARCHIVE) libAddressBook.a bintreeAddBook.o listAddBook.o

bintreeAddBook.o: bintreeAddBook.c bintreeAddBook.h
	$(CC) -c bintreeAddBook.c

listAddBook.o: listAddBook.c listAddBook.h
	$(CC) -c listAddBook.c

clean:
	@echo Removing executable file and object files...
	@rm *.o libAddressBook.a *.so

#Shared library:
LibAddressBook_so: so_listAddBook.o so_bintreeAddBook.o
	$(CC) -shared -o libAddressBook.so listAddBook.o bintreeAddBook.o

so_listAddBook.o: listAddBook.c listAddBook.h
	$(CC) -c -fPIC listAddBook.c -o listAddBook.o

so_bintreeAddBook.o: bintreeAddBook.c bintreeAddBook.h
	$(CC) -c -fPIC bintreeAddBook.c -o bintreeAddBook.o
