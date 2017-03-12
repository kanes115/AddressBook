#include "externals.h"
#include "listAddBook.h"


//private functions
BookRec_list* last_Book_list(BookRec_list* ptr){
  if(ptr == NULL)
    return NULL;

  struct BookRec_list* prev;

  while(ptr != NULL){
    prev = ptr;
    ptr = ptr -> next;
  }
  return prev;
}

void printRecord_Book_list(BookRec_list* ptr){
  assert(ptr != NULL);
  printf("%s, %s, %s, %s, %s, %s \n", ptr -> firstname, ptr -> lastname, ptr -> birthdate, ptr -> email, ptr -> phone, ptr -> address);
}

void print_Book_list(BookRec_list* first){
  if(first == NULL)
    printf("Empty book!\n");
  while(first != NULL){
    printRecord_Book_list(first);
    first = first -> next;
  }
}

bool isMatch_Book_list(BookRec_list* ptr, char* firstname, char* lastname){
  return strcmp(ptr -> firstname, firstname) == 0 && strcmp(ptr -> lastname, lastname) == 0;
}

BookRec_list* mallocSpace(char* firstname, char* lastname, char* birthdate,
                         char* email, char* phone, char* address){
  BookRec_list* res = malloc(sizeof(BookRec_list));
  res -> firstname = malloc(sizeof(char) * strlen(firstname));
  res -> lastname = malloc(sizeof(char) * strlen(lastname));
  res -> birthdate = malloc(sizeof(char) * strlen(birthdate));
  res -> email = malloc(sizeof(char) * strlen(email));
  res -> phone = malloc(sizeof(char) * strlen(phone));
  res -> address = malloc(sizeof(char) * strlen(address));
  return res;
}

void freeStructSpace(BookRec_list* ptr){
  free(ptr -> firstname);
  free(ptr -> lastname);
  free(ptr -> birthdate);
  free(ptr -> phone);
  free(ptr -> email);
  free(ptr -> address);
  free(ptr);
}

BookRec_list* getBiggestElement(BookRec_list* first, SORT_WITH sortwith){
  assert(sortwith <= 3 && sortwith >= 0);

  BookRec_list* maxPtr = first;
  char* max = "";
  char* tmp;

  while(first != NULL){
    switch(sortwith){
      case 0:
        tmp = first -> lastname;
        break;
      case 1:
        tmp = first -> birthdate;
        break;
      case 2:
        tmp = first -> email;
        break;
      case 3:
        tmp = first -> phone;
        break;
    }
    if(strcmp(max, tmp) < 0){
      max = tmp;
      maxPtr = first;
    }
    first = first -> next;
  }

  return maxPtr;
}
//------------------------------------------




//dodaje wpis do książki lub tworzy nową z tym wpsiem
BookRec_list* addRecord_Book_list(BookRec_list* first, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address){

  assert(firstname != NULL && lastname != NULL && email != NULL && phone != NULL && address != NULL);
  BookRec_list* tmp_f = first;

  first = mallocSpace(firstname, lastname, birthdate, email, phone, address);  //alokujemy pamięć i przypisujemy dane
  strcpy(first -> firstname, firstname);
  strcpy(first -> lastname, lastname);
  strcpy(first -> birthdate, birthdate);
  strcpy(first -> email, email);
  strcpy(first -> phone, phone);
  strcpy(first -> address, address);
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
BookRec_list* findRecord_Book_list(BookRec_list* first, char* firstname, char* lastname){

  assert(firstname != NULL && lastname != NULL);
  BookRec_list* prev;

  while(first != NULL && !isMatch_Book_list(first, firstname, lastname)){
    prev = first;
    first = first -> next;
  }

  return first;

}

//usuwa rekord pod przekazanym jako argument wskaźnikiem, z książki na której pierwszy element wskazuje first
//@NULLABLE
BookRec_list* deleteRecordAtPtr_Book_list(BookRec_list* first, BookRec_list* ptr){

  assert(ptr != NULL);

  BookRec_list* prev = ptr -> prev;
  BookRec_list* next = ptr -> next;

  freeStructSpace(ptr);
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
BookRec_list* deleteRecord_Book_list(BookRec_list* first, char* firstname, char* lastname){
  assert(firstname != NULL && lastname != NULL);

  BookRec_list* toDel = findRecord_Book_list(first, firstname, lastname);
  if(toDel != NULL)
    return deleteRecordAtPtr_Book_list(first, toDel);
  return first;
}

//usuwa całą książkę (wszystkie wpisy), zwraca pustą książkę (NULL)
//@NULLABLE
BookRec_list* deleteBook_Book_list(BookRec_list* first){

  BookRec_list* tmp;
  while(first != NULL){
    tmp = first;
    first = first -> next;
    free(tmp);
  }
  return NULL;    //zwracamy pustą książkę
}

//sortuje książkę
BookRec_list* sortBook_Book_list(BookRec_list* first, SORT_WITH sortwith){

  assert(sortwith >= 0 && sortwith <= 3);

  BookRec_list* newF = NULL;
  BookRec_list* currentBiggest;
  BookRec_list* tmp_prev;
  BookRec_list* tmp_next;
  BookRec_list* tmp;

  while(first != NULL){
    currentBiggest = getBiggestElement(first, sortwith);
    tmp_prev = currentBiggest -> prev;
    tmp_next = currentBiggest -> next;

    currentBiggest -> prev = NULL;    //"uziemiamy"
    currentBiggest -> next = NULL;

    if(tmp_prev == NULL)              //odpinamy największy element
      first = first -> next;
    else
      tmp_prev -> next = tmp_next;
    if(tmp_next != NULL) tmp_next -> prev = tmp_prev;

    tmp = newF;                       //podłączamy do nowej listy
    newF = currentBiggest;
    newF -> next = tmp;
    if(tmp != NULL) tmp -> prev = newF;
  }

  return newF;
}
