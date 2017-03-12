CC = gcc
SHARED_OPTS = -c -fPIC
ARCHIVE = ar rcs

all: LibAddressBook_st

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




#Karola:
# CC = gcc
#
# all: libcontact.o liblist.o libtree.o
# 	ar rcs libcb.a libcontact.o liblist.o libtree.o
# 	$(CC) -shared -o libcb.so libcontact.o liblist.o libtree.o
#
# libcontact.o: libcontact.c libcontact.h
# 	$(CC) -c -fpic libcontact.c -o libcontact.o
#
# liblist.o: liblist.c liblist.h
# 	$(CC) -c -fpic liblist.c -o liblist.o
#
# libtree.o: libtree.c libtree.h
# 	$(CC) -c -fpic libtree.c -o libtree.o
#
# clean:
# 	rm -f *.o *.so libcb.a
