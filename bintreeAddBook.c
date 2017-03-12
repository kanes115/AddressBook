#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/*
Książkę reprezentuje się jako strukturę Book_bin ze wskaźnikiem
root na korzeń drzewa.

Jeśli wskaźnik root jest NULLem, to znaczy, że jest to książka pusta.

ORGANIZED_BY to typ, który wykorystujemy do zaznaczenia wg jakiego
pola drzewo jest zorganizowane.

Szukać można po polu wg którego aktualnie drzewo jest zorganizowane
- inaczej niż w listowej implementacji
za domyślny stan przyjmujemy posortowanie.

*/



//typ mówiący o tym, wg czego zorganizowane jest drzewo
//0 - lastname
//1 - birthdate
//2 - email
//3 - phone
typedef int ORGANIZED_BY;

typedef struct BookRec_bin{
  char* firstname;
  char* lastname;
  char* birthdate;    //dla uproszczenia nie tworzyłem nowej struktury, sortowanie będzie działało dla formatu yyyy-mm-dd
  char* email;
  char* phone;
  char* address;

  struct BookRec_bin* right;
  struct BookRec_bin* left;
  struct BookRec_bin* parent;

}BookRec_bin;

typedef struct Book_bin{
  BookRec_bin* root;
  ORGANIZED_BY org;
}Book_bin;


//private functions

//alkouje miejsce w pamięci dla węzła drzewa
BookRec_bin* mallocSpace_bin(char* firstname, char* lastname, char* birthdate,
                         char* email, char* phone, char* address){
  BookRec_bin* res = malloc(sizeof(BookRec_bin));
  res -> firstname = malloc(sizeof(char) * strlen(firstname));
  res -> lastname = malloc(sizeof(char) * strlen(lastname));
  res -> birthdate = malloc(sizeof(char) * strlen(birthdate));
  res -> email = malloc(sizeof(char) * strlen(email));
  res -> phone = malloc(sizeof(char) * strlen(phone));
  res -> address = malloc(sizeof(char) * strlen(address));

  strcpy(res -> firstname, firstname);
  strcpy(res -> lastname, lastname);
  strcpy(res -> birthdate, birthdate);
  strcpy(res -> email, email);
  strcpy(res -> phone, phone);
  strcpy(res -> address, address);
  res -> right = NULL;
  res -> left = NULL;
  res -> parent = NULL;
  return res;
}

//wstawia element do niepustego drzewa
Book_bin* insertElement_bin(Book_bin* book, BookRec_bin* ins){

  BookRec_bin* root = book -> root;

  assert(root != NULL);

  BookRec_bin* res = root;
  BookRec_bin* prev;
  char* root_cmp;
  char* ins_cmp;

  while(root != NULL){
    switch (book -> org) {
      case 0:
        root_cmp = root -> lastname;
        ins_cmp = ins -> lastname;
        break;
      case 1:
        root_cmp = root -> birthdate;
        ins_cmp = ins -> birthdate;
        break;
      case 2:
        root_cmp = root -> email;
        ins_cmp = ins -> email;
        break;
      case 3:
        root_cmp = root -> phone;
        ins_cmp = ins -> phone;
        break;
    }


    prev = root;
    if(strcmp(root_cmp, ins_cmp) <= 0)
      root = root -> right;
    else
      root = root -> left;
  }

  if(strcmp(root_cmp, ins_cmp) <= 0)
    prev -> right = ins;
  else
    prev -> left = ins;
  ins -> parent = prev;

  book -> root = res;

  return book;
}

//wyświetla pojedynczy węzeł
void printSingleContact(BookRec_bin* elm){
  assert(elm != NULL);
  printf("%s, %s, %s, %s, %s, %s\n", elm -> firstname, elm -> lastname, elm -> birthdate, elm -> email, elm -> phone, elm -> address);
}

//wyswietla drzewo posortowane
void printBookFromRoot_bin(BookRec_bin* root){
  if(root == NULL)
    return;
  printBookFromRoot_bin(root -> left);
  printSingleContact(root);
  printBookFromRoot_bin(root -> right);
}

//dealokuje pamięc przeznaczoną na jeden węzeł
void freeStructSpace_bin(BookRec_bin* ptr){
  free(ptr -> firstname);
  free(ptr -> lastname);
  free(ptr -> birthdate);
  free(ptr -> phone);
  free(ptr -> email);
  free(ptr -> address);
  free(ptr);
}

//znajduje minimalną wartość w drzewie o root w root
BookRec_bin* findMin_bin(BookRec_bin* root){
  BookRec_bin* prev;
  while(root != NULL){
    prev = root;
    root = root -> left;
  }

  return prev;
}

//kopiuje zawartość rec1 do rec2
BookRec_bin* cpyRec_bin(BookRec_bin* rec1, BookRec_bin* rec2){
  rec1 -> lastname = realloc(rec1 -> lastname, sizeof(char) * strlen(rec2 -> lastname));
  strcpy(rec1 -> lastname, rec2 -> lastname);

  rec1 -> firstname = realloc(rec1 -> firstname, sizeof(char) * strlen(rec2 -> firstname));
  strcpy(rec1 -> firstname, rec2 -> firstname);

  rec1 -> birthdate = realloc(rec1 -> birthdate, sizeof(char) * strlen(rec2 -> birthdate));
  strcpy(rec1 -> birthdate, rec2 -> birthdate);

  rec1 -> email = realloc(rec1 -> email, sizeof(char) * strlen(rec2 -> email));
  strcpy(rec1 -> email, rec2 -> email);

  rec1 -> phone = realloc(rec1 -> phone, sizeof(char) * strlen(rec2 -> phone));
  strcpy(rec1 -> phone, rec2 -> phone);

  rec1 -> address = realloc(rec1 -> address, sizeof(char) * strlen(rec2 -> address));
  strcpy(rec1 -> address, rec2 -> address);

  return rec1;
}

//funkcję mówiące coś o rodzinie
bool hasBothChildren(BookRec_bin* ptr){
  return ptr -> right != NULL && ptr -> left != NULL;
}
bool isRoot(BookRec_bin* ptr){
  return ptr -> parent == NULL;
}
bool hasNoChildren(BookRec_bin* ptr){
  return ptr -> right == NULL && ptr -> left == NULL;
}
bool isRightChild(BookRec_bin* ptr){
  assert(ptr != NULL && ptr -> parent != NULL);
  return ptr -> parent -> right == ptr;
}
bool hasOnlyRightChild(BookRec_bin* ptr){
  return ptr -> right != NULL && ptr -> left == NULL;
}
bool hasOnlyLeftChild(BookRec_bin* ptr){
  return ptr -> right == NULL && ptr -> left != NULL;
}

//usuwa element, na który wskazuje toDel w książce book
Book_bin* delRecordAtPtr_bin(Book_bin* book, BookRec_bin* toDel){

  assert(toDel != NULL);

  //odłączanie od drzewa

  if(isRoot(toDel) && !hasBothChildren(toDel)){    //przypadek, gdy usuwamy roota, który nie ma kompletu dzieci
    if(hasNoChildren(toDel))
      book -> root = NULL;
    else if(hasOnlyRightChild(toDel))
      book -> root = toDel -> right;
    else if(hasOnlyLeftChild(toDel))
      book -> root = toDel -> left;
  }


  else if(hasNoChildren(toDel)){                    //nie ma dzieci
    if(isRightChild(toDel))                         //jest prawym dzieckiem
      toDel -> parent -> right = NULL;
    else                                            //jest lewym dzieckiem
      toDel -> parent -> left = NULL;
  }
  else if(hasOnlyRightChild(toDel)){               //ma tylko prawe dziecko
    if(isRightChild(toDel))                        //jest prawym dzieckiem
      toDel -> parent -> right = toDel -> right;
    else                                            //jest lewym dzieckiem
      toDel -> parent -> left = toDel -> right;
  }
  else if(hasOnlyLeftChild(toDel)){                 //ma tylko lewe dziecko
    if(isRightChild(toDel))                         //jest prawym dzieckiem
      toDel -> parent -> right = toDel -> left;
    else                                            //jest lewym dzieckiem
      toDel -> parent -> left = toDel -> left;
  }
  else if(hasBothChildren(toDel)){                               // ma obydwoje dzieci
    BookRec_bin* min = findMin_bin(toDel -> right);              //znajdź najmniejszy element w prawym poddrzewie usuwanego - następnika
    cpyRec_bin(toDel, min);                                      //skopiuj zawartość następnika do usuwanego
    return delRecordAtPtr_bin(book, min);                        //usuń następnika
  }

  //zwalnianie pamięci i zwrócenie struktury
  freeStructSpace_bin(toDel);
  return book;
}

//usuwa całe drzewo od roota
void deleteBookFromPtr_bin(BookRec_bin* root){
  if(root == NULL)
    return;

  deleteBookFromPtr_bin(root -> left);
  BookRec_bin* right = root ->right;
  freeStructSpace_bin(root);
  deleteBookFromPtr_bin(right);
}
//-----------------



//wyświetla książkę
void printBook_bin(Book_bin* book){
  printBookFromRoot_bin(book -> root);
}

//stwarza pustą książkę
Book_bin* createEmptyAddBook_bin(ORGANIZED_BY org){
  assert(org >= 0 && org <= 3);
  Book_bin* res = malloc(sizeof(Book_bin));
  res -> org = org;
  res -> root = NULL;
  return res;
}

//dodaje element do książki
Book_bin* addRecord_bin(Book_bin* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address){

  BookRec_bin* root = book -> root;

  BookRec_bin* ins = mallocSpace_bin(firstname, lastname, birthdate, email, phone, address);


  if(root == NULL){
    book -> root = ins;
    return book;
  }

  return insertElement_bin(book, ins);
}

//znajduje element o podanych danych (szuka po elementach, po których jest zorganizowana)
//@NULLABLE
BookRec_bin* findElement_bin(Book_bin* book, char* phrase){

  BookRec_bin* root = book -> root;
  if(root == NULL)  //pusta książka
    return NULL;

  BookRec_bin* prev;
  char* root_cmp;

  while(root != NULL){
    switch (book -> org) {
      case 0:
        root_cmp = root -> lastname;
        break;
      case 1:
        root_cmp = root -> birthdate;
        break;
      case 2:
        root_cmp = root -> email;
        break;
      case 3:
        root_cmp = root -> phone;
        break;
    }


    if(strcmp(root_cmp, phrase) == 0)
      return root;

    prev = root;
    if(strcmp(root_cmp, phrase) <= 0)
      root = root -> right;
    else
      root = root -> left;
  }

  return NULL;

}

//usuwa element z książki, jeśli element nie istnieje - nic nie robi
Book_bin* delRecord_bin(Book_bin* book, char* phrase){
  BookRec_bin* toDel = findElement_bin(book, phrase);
  if(toDel == NULL)       //nie znalezniono elementu
    return book;

  return delRecordAtPtr_bin(book, toDel);
}

//usuwa całą książkę
void deleteBook_bin(Book_bin* book){
  deleteBookFromPtr_bin(book -> root);
  free(book);
}
