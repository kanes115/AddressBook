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


//wyświetla książkę
void printBook_bin(Book_bin* book);

//stwarza pustą książkę
Book_bin* createEmptyAddBook_bin(ORGANIZED_BY org);

//dodaje element do książki
Book_bin* addRecord_bin(Book_bin* book, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address);

//znajduje element o podanych danych (szuka po elementach, po których jest zorganizowana)
//@NULLABLE
BookRec_bin* findElement_bin(Book_bin* book, char* phrase);

//usuwa element z książki, jeśli element nie istnieje - nic nie robi
Book_bin* delRecord_bin(Book_bin* book, char* phrase);

//usuwa całą książkę
void deleteBook_bin(Book_bin* book);

//przebudowuje drzewo wg klucza
Book_bin* rebuild_bin(Book_bin* book, ORGANIZED_BY org);
