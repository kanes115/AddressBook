#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/*
Książkę reprezentuje się jako wskaźnik na jej pierwszy element.
Jeśli wskaźnik ten jest NULLem, to znaczy, że jest to książka pusta.
Po czym sortujemy oznaczamy intem
*/

typedef int SORT_WITH;


typedef struct BookRec_bin{
  char* firstname;
  char* lastname;     //sortwith = 0
  char* birthdate;    //dla uproszczenia nie tworzyłem nowej struktury, sortowanie będzie działało dla formatu yyyy-mm-dd, sortwith = 1
  char* email;        //sortwith = 2
  char* phone;        //sortwith = 3
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
  return strcmp(ptr -> firstname, firstname) == 0 && strcmp(ptr -> lastname, lastname) == 0;
}

BookRec_bin* mallocSpace(char* firstname, char* lastname, char* birthdate,
                         char* email, char* phone, char* address){
  BookRec_bin* res = malloc(sizeof(BookRec_bin));
  res -> firstname = malloc(sizeof(char) * strlen(firstname));
  res -> lastname = malloc(sizeof(char) * strlen(lastname));
  res -> birthdate = malloc(sizeof(char) * strlen(birthdate));
  res -> email = malloc(sizeof(char) * strlen(email));
  res -> phone = malloc(sizeof(char) * strlen(phone));
  res -> address = malloc(sizeof(char) * strlen(address));
  return res;
}

void freeStructSpace(BookRec_bin* ptr){
  free(ptr -> firstname);
  free(ptr -> lastname);
  free(ptr -> birthdate);
  free(ptr -> phone);
  free(ptr -> email);
  free(ptr -> address);
  free(ptr);
}

BookRec_bin* getBiggestElement(BookRec_bin* first, SORT_WITH sortwith){
  assert(sortwith <= 3 && sortwith >= 0);

  BookRec_bin* maxPtr = first;
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
BookRec_bin* addRecord_Book_bin(BookRec_bin* first, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address){

  BookRec_bin* tmp_f = first;

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
BookRec_bin* sortBook_Book_bin(BookRec_bin* first, SORT_WITH sortwith){

  BookRec_bin* newF = NULL;
  BookRec_bin* currentBiggest;
  BookRec_bin* tmp_prev;
  BookRec_bin* tmp_next;
  BookRec_bin* tmp;

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
