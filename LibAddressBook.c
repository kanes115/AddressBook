#include <stdio.h>
#include <string.h>
#include "listAddBook.c"
#include "bintreeAddBook.c"

int main(int argc, char* argv []){
  Book_bin* book = createEmptyAddBook_bin(0);
  book = addRecord_bin(book, "lol", "D", "", "D@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "rotfl", "B", "", "B@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "haha", "A", "555", "A@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "xaxa", "C", "", "C@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "iksde", "F", "", "F@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "xd", "Z", "", "Z@icloud.com", "694555556", "Sucha Beskidzka");
  printBook_bin(book);
  printf("---------------\n");
  book = delRecord_bin(book, argv[1]);
  printBook_bin(book);
  deleteBook_bin(book);
}
