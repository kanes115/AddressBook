#include <stdio.h>
#include <string.h>
#include "listAddBook.h"
#include "bintreeAddBook.h"

int main(int argc, char* argv []){
  Book_bin* book = createEmptyAddBook_bin(0);
  book = addRecord_bin(book, "lol", "D", "3", "F@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "rotfl", "B", "9", "H@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "haha", "A", "555", "O@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "xaxa", "C", "", "C@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "iksde", "F", "", "Z@icloud.com", "694555556", "Sucha Beskidzka");
  book = addRecord_bin(book, "xd", "Z", "", "D@icloud.com", "694555556", "Sucha Beskidzka");
  printBook_bin(book);
  printf("---------------\n");
  book = rebuild_bin(book, 1);
  printBook_bin(book);
}
