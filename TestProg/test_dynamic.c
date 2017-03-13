#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "../listAddBook.h"
#include "../bintreeAddBook.h"
#include "basetoTest.c"


//Bintree

Book_bin* time_createRandomBook_bin(int n, FILE* file, void* handle){
  // załadowanie funkcji
  Book_bin* (*createEmptyAddBook_bin)(ORGANIZED_BY);
  Book_bin* (*addRecord_bin)(Book_bin*, char*, char*, char*, char*, char*, char*);

  createEmptyAddBook_bin = dlsym(handle, "createEmptyAddBook_bin");
  addRecord_bin = dlsym(handle, "addRecord_bin");

  char* error = dlerror();
   if (error != NULL) {
     fprintf(stderr, "%s\n", error);
     return NULL;
    }


  //operacja
  start_clock();

  Book_bin* res = (*createEmptyAddBook_bin)(0);
  for(int i = 0; i < n; i++){
    res = (*addRecord_bin)(res, randstring(10), randstring(10), randstring(10), randstring(10), randstring(10), randstring(10));
  }

  fprintf(file, "Creation of %d - element bintree\n", n);
  double elps = end_clock(file);
  printf("Creation of %d - element bintree done in %f s\n", n, elps);

  return res;
}

Book_bin* time_addElement_bin(Book_bin* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address, FILE* file, void* handle){
  // załadowanie funkcji
  Book_bin* (*addRecord_bin)(Book_bin*, char*, char*, char*, char*, char*, char*);

  addRecord_bin = dlsym(handle, "addRecord_bin");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }


  //operacja
  start_clock();

  Book_bin* res = (*addRecord_bin)(book, firstname, lastname, birthdate,
                                       email, phone, address);

  fprintf(file, "Adding element to bintree\n");
  double elps = end_clock(file);

  printf("Adding element to bintree done in %f s\n", elps);

  return res;
}

Book_bin* time_delElement_bin(Book_bin* book, char* phrase, FILE* file, void* handle){

  // załadowanie funkcji
  Book_bin* (*delRecord_bin)(Book_bin*, char*);

  delRecord_bin = dlsym(handle, "delRecord_bin");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }


  //operacja
  start_clock();

  Book_bin* res = (*delRecord_bin)(book, phrase);

  fprintf(file, "Removing element from bintree\n");
  double elps = end_clock(file);
  printf("Removing element from bintree done in %f s\n", elps);

  return res;
}

BookRec_bin* time_findElement_bin(Book_bin* book, char* phrase, FILE* file, void* handle){
  // załadowanie funkcji
  BookRec_bin* (*findElement_bin)(Book_bin*, char*);

  findElement_bin = dlsym(handle, "findElement_bin");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }


  //operacja
  start_clock();

  BookRec_bin* res = (*findElement_bin)(book, phrase);

  fprintf(file, "Finding element in bintree\n");
  double elps = end_clock(file);
  printf("Finding element in bintree done in %f s\n", elps);

  return res;
}

Book_bin* time_rebuild_bin(Book_bin* book, FILE* file, void* handle){
  // załadowanie funkcji
  Book_bin* (*rebuild_bin)(Book_bin*, int);

  rebuild_bin = dlsym(handle, "rebuild_bin");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }



  start_clock();

  Book_bin* res = (*rebuild_bin)(book, 1);

  fprintf(file, "Rebuilding bintree done\n");
  double elps = end_clock(file);
  printf("Rebuilding bintree done in %f s\n", elps);

  return res;
}

//List

BookRec_list* time_createRandomBook_list(int n, FILE* file, void* handle){
  // załadowanie funkcji
  BookRec_list* (*addRecord_Book_list)(BookRec_list*, char*, char*, char*, char*, char*, char*);

  addRecord_Book_list = dlsym(handle, "addRecord_Book_list");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
  }

  //operacja
  start_clock();

  BookRec_list* book = NULL;

  for(int i = 0; i < n; i++){
    book = (*addRecord_Book_list)(book, randstring(10), randstring(10), randstring(10), randstring(10), randstring(10), randstring(10));
  }

  fprintf(file, "Creation of %d - element list book\n", n);
  double elps = end_clock(file);
  printf("Creation of %d - element list book done in %f s\n", n, elps);

  return book;
}

BookRec_list* time_addElement_list(BookRec_list* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address, FILE* file, void* handle){

  // załadowanie funkcji
  BookRec_list* (*addRecord_Book_list)(BookRec_list*, char*, char*, char*, char*, char*, char*);

  addRecord_Book_list = dlsym(handle, "addRecord_Book_list");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
    }


  start_clock();

  BookRec_list* res =  (*addRecord_Book_list)(book, firstname, lastname, birthdate,
                                       email, phone, address);

  fprintf(file, "Adding element to list book\n");
  double elps = end_clock(file);
  printf("Adding element to list book done in %f s\n", elps);

  return res;
}

BookRec_list* time_delElement_list(BookRec_list* book, char* firstname, char* lastname, FILE* file, void* handle){
  // załadowanie funkcji
  BookRec_list* (*deleteRecord_Book_list)(BookRec_list*, char*, char*);

  deleteRecord_Book_list = dlsym(handle, "deleteRecord_Book_list");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
    }

    //operacja
  start_clock();

  BookRec_list* res = (*deleteRecord_Book_list)(book, firstname, lastname);

  fprintf(file, "Removing element from list book\n");
  double elps = end_clock(file);
  printf("Removing element from list book done in %f s\n", elps);

  return res;
}

BookRec_list* time_findElement_list(BookRec_list* book, char* firstname, char* lastname, FILE* file, void* handle){
  // załadowanie funkcji
  BookRec_list* (*findRecord_Book_list)(BookRec_list*, char*, char*);

  findRecord_Book_list = dlsym(handle, "findRecord_Book_list");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
    }

  //operacja
  start_clock();

  BookRec_list* res = (*findRecord_Book_list)(book, firstname, lastname);

  fprintf(file, "Finding element in list book\n");
  double elps = end_clock(file);
  printf("Finding element in list book done in %f s\n", elps);

  return res;
}

BookRec_list* time_rebuild_list(BookRec_list* book, FILE* file, void* handle){
  // załadowanie funkcji
  BookRec_list* (*sortBook_Book_list)(BookRec_list*, int);

  sortBook_Book_list = dlsym(handle, "sortBook_Book_list");

  char* error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    return NULL;
    }


  //operacja
  start_clock();

  BookRec_list* res = (*sortBook_Book_list)(book, 1);

  fprintf(file, "Rebuilding list book done\n");
  double elps = end_clock(file);
  printf("Rebuilding list book done in %f s\n", elps);

  return res;
}


void runBintree(FILE* res, void* handle, int n){
  printf("--- BINTREE IMPLEMENTATION TESTS ---\n");
  fprintf(res, "--- BINTREE IMPLEMENTATION TESTS ---\n");

  Book_bin* book = time_createRandomBook_bin(n, res, handle);

  book = time_addElement_bin(book, "z", "g", "z", "z", "z", "z", res, handle);

  time_findElement_bin(book, "g", res, handle);

  book = time_delElement_bin(book, "g", res, handle);

  book = time_rebuild_bin(book, res, handle);
}

void runList(FILE* res, void* handle, int n){
  printf("--- LIST IMPLEMENTATION TESTS ---\n");
  fprintf(res, "--- LIST IMPLEMENTATION TESTS ---\n");

  BookRec_list* book2 = time_createRandomBook_list(n, res, handle);

  book2 = time_addElement_list(book2, "z", "g", "z", "z", "z", "z", res, handle);

  time_findElement_list(book2, "z", "g", res, handle);

  book2 = time_delElement_list(book2, "z", "g", res, handle);

  book2 = time_rebuild_list(book2, res, handle);
}



int main(int argc, char* argv []){

  void* handle;
  handle = dlopen("../libAddressBook.so", RTLD_LAZY);
  char* error;
  if (!handle){
    fprintf(stderr, "%s\n", dlerror());
    return 1;
  }

  FILE* res = openFile();

  runBintree(res, handle, 1000);
  runList(res, handle, 1000);
  fprintf(res, "=====================================\n\n\n\n");


  dlclose(handle);
  fclose(res);


}
