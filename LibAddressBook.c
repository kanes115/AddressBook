#include <stdio.h>
#include "binTreeAddBook.c"

int main(int argc, char* argv []){
  struct BookRec_bin* first = addRecord_Book_bin(NULL, "Dominik", "Stanaszek", "1996-02-28", "fff@gmail.com", "694555556", "Sucha");
  first = addRecord_Book_bin(first, "Agnieszka", "Pierzchala", "1996-12-04", "aga.zmc@gmail.com", "5353345", "Zamosc");
  first = addRecord_Book_bin(first, "Tomek", "Kurek", "1997-02-09", "g.g@gmail.com", "6666", "Zamosc");
  print_Book_bin(first);
  printf("-----------\n");
  

}
