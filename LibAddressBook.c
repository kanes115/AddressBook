#include <stdio.h>
#include <string.h>
#include "listAddBook.c"
#include "bintreeAddBook.c"

int main(int argc, char* argv []){
  Book_bin* book = createEmptyAddBook_bin(0);
  book = addRecord_bin(book, "", "S", "", "dominikstanaszek@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "", "A", "", "dominikstanaszek@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "", "Z", "", "dominikstanaszek@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "", "B", "", "dominikstanaszek@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "", "C", "", "dominikstanaszek@icloud.com", "694555556", "Sucha Beskidzka");
  printBook_bin(book);
  printf("---------------\n");
  book = delRecord_bin(book, argv[1]);
  printBook_bin(book);
}
