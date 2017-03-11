#include <stdio.h>
#include <string.h>
#include "binTreeAddBook.c"

int main(int argc, char* argv []){
  struct BookRec_list* first = addRecord_Book_list(NULL, "Dominik", "G", "1996-02-28", "fff@gmail.com", "694555556", "Sucha");
  first = addRecord_Book_list(first, "Katarzyna", "Z", "1996-02-17", "kbanaszka@icloud.com", "ddddd", "Skowronki");
  first = addRecord_Book_list(first, "Agnieszka", "D", "1996-12-04", "aga.zmc@gmail.com", "5353345", "Zamosc");
  first = addRecord_Book_list(first, "Agnieszka", "A", "1996-12-04", "aga.zmc@gmail.com", "5353345", "Zamosc");
  first = addRecord_Book_list(first, "Tomek", "C", "1997-02-09", "g.g@gmail.com", "6666", "Rybnik");
  first = addRecord_Book_list(first, "Tomek", "B", "1997-02-09", "g.g@gmail.com", "6666", "Rybnik");
  print_Book_list(first);
  printf("-----------\n");
  first = sortBook_Book_list(first, 0);
  print_Book_list(first);

}
