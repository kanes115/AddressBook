#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include "basetoTest.c"
#include "../listAddBook.h"
#include "../bintreeAddBook.h"


//Bintree

Book_bin* time_createRandomBook_bin(int n, FILE* file){
  start_clock();

  Book_bin* res = createEmptyAddBook_bin(0);
  for(int i = 0; i < n; i++){
    res = addRecord_bin(res, randstring(10), randstring(10), randstring(10), randstring(10), randstring(10), randstring(10));
  }

  fprintf(file, "Creation of %d - element bintree\n", n);
  double realtime = end_clock(file);
  printf("Creation of %d - element bintree done in %f ms\n", n, realtime);

  return res;
}

Book_bin* time_addElement_bin(Book_bin* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address, FILE* file){
  start_clock();

  Book_bin* res =  addRecord_bin(book, firstname, lastname, birthdate,
                                       email, phone, address);


  fprintf(file, "Adding element to bintree\n");
  double cpu_time_used = end_clock(file);
  printf("Adding element to bintree done in %f s\n", cpu_time_used);

  return res;
}

Book_bin* time_delElement_bin(Book_bin* book, char* phrase, FILE* file){
  start_clock();

  Book_bin* res = delRecord_bin(book, phrase);

  fprintf(file, "Removing element from bintree\n");
  double cpu_time_used = end_clock(file);
  printf("Removing element from bintree done in %f s\n", cpu_time_used);

  return res;
}

BookRec_bin* time_findElement_bin(Book_bin* book, char* phrase, FILE* file){
  start_clock();

  BookRec_bin* res = findElement_bin(book, phrase);

  fprintf(file, "Finding element in bintree\n");
  double cpu_time_used = end_clock(file);
  printf("Finding element in bintree done in %f s\n", cpu_time_used);

  return res;
}

Book_bin* time_rebuild_bin(Book_bin* book, FILE* file){
  start_clock();

  Book_bin* res = rebuild_bin(book, 1);

  fprintf(file, "Rebuilding bintree\n");
  double cpu_time_used = end_clock(file);
  printf("Rebuilding bintree done in %f s\n", cpu_time_used);

  return res;
}

//List

BookRec_list* time_createRandomBook_list(int n, FILE* file){
  start_clock();

  BookRec_list* book = NULL;

  for(int i = 0; i < n; i++){
    book = addRecord_Book_list(book, randstring(10), randstring(10), randstring(10), randstring(10), randstring(10), randstring(10));
  }

  fprintf(file, "Creation of %d - element list book\n", n);
  double cpu_time_used = end_clock(file);
  printf("Creation of %d - element list book done in %f s\n", n, cpu_time_used);

  return book;
}

BookRec_list* time_addElement_list(BookRec_list* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address, FILE* file){
  start_clock();

  BookRec_list* res =  addRecord_Book_list(book, firstname, lastname, birthdate,
                                       email, phone, address);

  fprintf(file, "Adding element to list book\n");
  double cpu_time_used = end_clock(file);
  printf("Adding element to list book done in %f s\n", cpu_time_used);

  return res;
}

BookRec_list* time_delElement_list(BookRec_list* book, char* firstname, char* lastname, FILE* file){
  start_clock();

  BookRec_list* res = deleteRecord_Book_list(book, firstname, lastname);

  fprintf(file, "Removing element from list book\n");
  double cpu_time_used = end_clock(file);
  printf("Removing element from list book done in %f s\n", cpu_time_used);

  return res;
}

BookRec_list* time_findElement_list(BookRec_list* book, char* firstname, char* lastname, FILE* file){
  start_clock();

  BookRec_list* res = findRecord_Book_list(book, firstname, lastname);

  fprintf(file, "Finding element in list book\n");
  double cpu_time_used = end_clock(file);
  printf("Finding element in list book done in %f s\n", cpu_time_used);

  return res;
}

BookRec_list* time_rebuild_list(BookRec_list* book, FILE* file){
  start_clock();

  BookRec_list* res = sortBook_Book_list(book, 1);

  fprintf(file, "Rebuilding list book");
  double cpu_time_used = end_clock(file);
  printf("Rebuilding list book done in %f s\n", cpu_time_used);

  return res;
}

//Running tests

void runBintree(FILE* res, int n){
  printf("--- BINTREE IMPLEMENTATION TESTS ---\n");
  fprintf(res, "--- BINTREE IMPLEMENTATION TESTS ---\n");

  Book_bin* book = time_createRandomBook_bin(n, res);

  book = time_addElement_bin(book, "z", "g", "z", "z", "z", "z", res);

  time_findElement_bin(book, "g", res);

  book = time_delElement_bin(book, "g", res);

  book = time_rebuild_bin(book, res);
}

void runList(FILE* res, int n){
  printf("--- LIST IMPLEMENTATION TESTS ---\n");
  fprintf(res, "--- LIST IMPLEMENTATION TESTS ---\n");

  BookRec_list* book2 = time_createRandomBook_list(n, res);

  book2 = time_addElement_list(book2, "z", "g", "z", "z", "z", "z", res);

  time_findElement_list(book2, "z", "g", res);

  book2 = time_delElement_list(book2, "z", "g", res);

  book2 = time_rebuild_list(book2, res);
}


int main(int argc, char* argv []){

  FILE *res = openFile();

  runList(res, 1000);
  runBintree(res, 1000);
  fprintf(res, "=====================================\n\n\n\n");

  fclose(res);

}
