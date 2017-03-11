#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/*
Książkę reprezentuje się jako wskaźnik na jej pierwszy element.
Jeśli wskaźnik ten jest NULLem, to znaczy, że jest to książka pusta.
*/


typedef struct BookRec_bin{
  char* firstname;
  char* lastname;
  char* birthdate;    //dla uproszczenia nie tworzyłem nowej struktury, sortowanie będzie działało dla formatu yyyy-mm-dd
  char* email;
  char* phone;
  char* address;

  struct BookRec_bin* next;
  struct BookRec_bin* prev;
}BookRec_bin;

//private functions
BookRec_bin* last_Book_bin(BookRec_bin* ptr){
  if(ptr == NULL)
    return NULL;

  struct BookRec_bin* prev;

  while(ptr != NULL){
    prev = ptr;
    ptr = ptr -> next;
  }
  return prev;
}

void printRecord_Book_bin(BookRec_bin* ptr){
  assert(ptr != NULL);
  printf("%s, %s, %s, %s, %s, %s \n", ptr -> firstname, ptr -> lastname, ptr -> birthdate, ptr -> email, ptr -> phone, ptr -> address);
}

void print_Book_bin(BookRec_bin* first){
  if(first == NULL)
    printf("Empty book!\n");
  while(first != NULL){
    printRecord_Book_bin(first);
    first = first -> next;
  }
}

bool isMatch_Book_bin(BookRec_bin* ptr, char* firstname, char* lastname){
  return ptr -> firstname == firstname && ptr -> lastname == lastname;
}
//------------------------------------------




//dodaje wpis do książki lub tworzy nową z tym wpsiem
BookRec_bin* addRecord_Book_bin(BookRec_bin* first, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address){

  BookRec_bin* tmp_f = first;

  first = malloc(sizeof(BookRec_bin));  //alokujemy pamięć i przypisujemy dane
  first -> firstname = firstname;
  first -> lastname = lastname;
  first -> birthdate = birthdate;
  first -> email = email;
  first -> phone = phone;
  first -> address = address;
  first -> next = NULL;
  first -> prev = NULL;

  if(tmp_f == NULL){     //tworzymy nową książkę
    return first;
  }

  first -> next = tmp_f;  //tylko dodajemy wpis
  tmp_f -> prev = first;

  return first;

}

//zwraca wskaźnik do znaleznionego elementu (jeśli nie znalezniono to NULL)
//@NULLABLE
BookRec_bin* findRecord_Book_bin(BookRec_bin* first, char* firstname, char* lastname){

  BookRec_bin* prev;

  while(first != NULL && !isMatch_Book_bin(first, firstname, lastname)){
    prev = first;
    first = first -> next;
  }

  return first;

}

//usuwa rekord pod przekazanym jako argument wskaźnikiem, z książki na której pierwszy element wskazuje first
//@NULLABLE
BookRec_bin* deleteRecordAtPtr_Book_bin(BookRec_bin* first, BookRec_bin* ptr){

  assert(ptr != NULL);

  BookRec_bin* prev = ptr -> prev;
  BookRec_bin* next = ptr -> next;

  free(ptr);
  if(prev == NULL && next == NULL)
    return NULL;
  if(prev == NULL){     //usuwamy pierwsyz element
    next -> prev = NULL;
    return next;
  }
  prev -> next = next;
  if(next != NULL)
    next -> prev = prev;
  return first;
}

//usuwa rekord o podanym imieniu i nazwisku, zwraca wskaźnik na pierwszy element nowej listy,
//jeśli element nie istnieje w książce, nic nie usuwa
BookRec_bin* deleteRecord_Book_bin(BookRec_bin* first, char* firstname, char* lastname){
  BookRec_bin* toDel = findRecord_Book_bin(first, firstname, lastname);
  if(toDel != NULL)
    return deleteRecordAtPtr_Book_bin(first, toDel);
  return first;
}

//usuwa całą książkę (wszystkie wpisy), zwraca pustą książkę (NULL)
//@NULLABLE
BookRec_bin* deleteBook_Book_bin(BookRec_bin* first){

  BookRec_bin* tmp;
  while(first != NULL){
    tmp = first;
    first = first -> next;
    free(tmp);
  }
  return NULL;    //zwracamy pustą książkę
}

//sortuje książkę
BookRec_bin* sortBook_Book_bin(BookRec_bin* first){

  BookRec_bin* newF;

  
}
