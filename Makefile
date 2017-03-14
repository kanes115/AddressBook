CC = gcc
SHARED_OPTS = -c -fPIC
ARCHIVE = ar rcs
OPT= 2
GDB = -g
STATIC_OUT = libAddressBook.a
SHARED_OUT = libAddressBook.so

static: LibAddressBook_st

shared: LibAddressBook_so


#Static library:
LibAddressBook_st: bintreeAddBook.o listAddBook.o
	$(ARCHIVE) $(STATIC_OUT) bintreeAddBook.o listAddBook.o

bintreeAddBook.o: bintreeAddBook.c bintreeAddBook.h
	$(CC) -O$(OPT) $(GDB) -c bintreeAddBook.c

listAddBook.o: listAddBook.c listAddBook.h
	$(CC) -O$(OPT) $(GDB) -c listAddBook.c

clean:
	@echo Removing executable file and object files...
	@rm -f *.o $(STATIC_OUT) $(SHARED_OUT)

#Shared library:
LibAddressBook_so: so_listAddBook.o so_bintreeAddBook.o
	$(CC) -O$(OPT) $(GDB) -shared -o $(SHARED_OUT) listAddBook.o bintreeAddBook.o

so_listAddBook.o: listAddBook.c listAddBook.h
	$(CC) -c -O$(OPT) $(GDB) -fPIC listAddBook.c -o listAddBook.o

so_bintreeAddBook.o: bintreeAddBook.c bintreeAddBook.h
	$(CC) -c -O$(OPT) $(GDB) -fPIC bintreeAddBook.c -o bintreeAddBook.o
