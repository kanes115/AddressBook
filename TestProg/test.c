#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include "../listAddBook.h"
#include "../bintreeAddBook.h"

char *randstring(int length) {
    static int mySeed = 25011984;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    size_t stringLen = strlen(string);
    char *randomString = NULL;

    srand(time(NULL) * length + ++mySeed);

    if (length < 1) {
        length = 1;
    }

    randomString = malloc(sizeof(char) * (length +1));

    if (randomString) {
        short key = 0;

        for (int n = 0;n < length;n++) {
            key = rand() % stringLen;
            randomString[n] = string[key];
        }

        randomString[length] = '\0';

        return randomString;
    }
    else {
        printf("No memory");
        exit(1);
    }
}

//Bintree

Book_bin* time_createRandomBook_bin(int n){
  clock_t start = clock();

  Book_bin* res = createEmptyAddBook_bin(0);
  for(int i = 0; i < n; i++){
    res = addRecord_bin(res, randstring(10), randstring(10), randstring(10), randstring(10), randstring(10), randstring(10));
  }

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Creation of %d - element bintree done in %f s\n", n, cpu_time_used);

  return res;
}

Book_bin* time_addElement_bin(Book_bin* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address){
  clock_t start = clock();

  Book_bin* res =  addRecord_bin(book, firstname, lastname, birthdate,
                                       email, phone, address);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Adding element to bintree done in %f s\n", cpu_time_used);

  return res;
}

Book_bin* time_delElement_bin(Book_bin* book, char* phrase){
  clock_t start = clock();

  Book_bin* res = delRecord_bin(book, phrase);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Removing element from bintree done in %f s\n", cpu_time_used);

  return res;
}

BookRec_bin* time_findElement_bin(Book_bin* book, char* phrase){
  clock_t start = clock();

  BookRec_bin* res = findElement_bin(book, phrase);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Finding element in bintree done in %f s\n", cpu_time_used);

  return res;
}

Book_bin* time_rebuild_bin(Book_bin* book){
  clock_t start = clock();

  Book_bin* res = rebuild_bin(book, 1);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Rebuilding bintree done in %f s\n", cpu_time_used);

  return res;
}

//List

BookRec_list* time_createRandomBook_list(int n){
  clock_t start = clock();

  BookRec_list* book = NULL;

  for(int i = 0; i < n; i++){
    book = addRecord_Book_list(book, randstring(10), randstring(10), randstring(10), randstring(10), randstring(10), randstring(10));
  }


  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Creation of %d - element list book done in %f s\n", n, cpu_time_used);

  return book;
}

BookRec_list* time_addElement_list(BookRec_list* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address){
  clock_t start = clock();

  BookRec_list* res =  addRecord_Book_list(book, firstname, lastname, birthdate,
                                       email, phone, address);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Adding element to list book done in %f s\n", cpu_time_used);

  return res;
}

BookRec_list* time_delElement_list(BookRec_list* book, char* firstname, char* lastname){
  clock_t start = clock();

  BookRec_list* res = deleteRecord_Book_list(book, firstname, lastname);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Removing element from list book done in %f s\n", cpu_time_used);

  return res;
}

BookRec_list* time_findElement_list(BookRec_list* book, char* firstname, char* lastname){
  clock_t start = clock();

  BookRec_list* res = findRecord_Book_list(book, firstname, lastname);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Finding element in list book done in %f s\n", cpu_time_used);

  return res;
}

BookRec_list* time_rebuild_list(BookRec_list* book){
  clock_t start = clock();

  BookRec_list* res = sortBook_Book_list(book, 1);

  clock_t end = clock();
  double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Rebuilding list book done in %f s\n", cpu_time_used);

  return res;
}

int main(int argc, char* argv []){


  FILE *fp = fopen("scores.txt", "ab+");

  




  printf("--- BINTREE IMPLEMENTATION TESTS ---\n");
  Book_bin* book = time_createRandomBook_bin(10000);

  book = time_addElement_bin(book, "z", "g", "z", "z", "z", "z");

  time_findElement_bin(book, "g");

  book = time_delElement_bin(book, "g");

  book = time_rebuild_bin(book);

  printf("--- LIST IMPLEMENTATION TESTS ---\n");

  BookRec_list* book2 = time_createRandomBook_list(10000);

  book2 = time_addElement_list(book2, "z", "g", "z", "z", "z", "z");

  time_findElement_list(book2, "z", "g");

  book2 = time_delElement_list(book2, "z", "g");

  book2 = time_rebuild_list(book2);











}
