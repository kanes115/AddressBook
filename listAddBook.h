/*
Książkę reprezentuje się jako wskaźnik na jej pierwszy element.

Jeśli wskaźnik ten jest NULLem, to znaczy, że jest to książka pusta.

To po czym sortujemy determinuje SORT_WITH.

Szukać można po imieniu i nazwisku - inaczej niż w drzewiastej implementacji
za domyślny stan przyjmujemy nieposrtowanie. Posortować można dodatkowo funkcją
sortBook.

*/

//typ mówiący o tym, po czym sortujemy
//0 - lastname
//1 - birthdate
//2 - email
//3 - phone
typedef int SORT_WITH;


typedef struct BookRec_list{
  char* firstname;
  char* lastname;
  char* birthdate;    //dla uproszczenia nie tworzyłem nowej struktury, sortowanie będzie działało dla formatu yyyy-mm-dd
  char* email;
  char* phone;
  char* address;

  struct BookRec_list* next;
  struct BookRec_list* prev;
}BookRec_list;


BookRec_list* addRecord_Book_list(BookRec_list* first, char* firstname, char* lastname, char* birthdate,
                                       char* email, char* phone, char* address);

BookRec_list* findRecord_Book_list(BookRec_list* first, char* firstname, char* lastname);


BookRec_list* deleteRecordAtPtr_Book_list(BookRec_list* first, BookRec_list* ptr);


BookRec_list* deleteRecord_Book_list(BookRec_list* first, char* firstname, char* lastname);


BookRec_list* deleteBook_Book_list(BookRec_list* first);


BookRec_list* sortBook_Book_list(BookRec_list* first, SORT_WITH sortwith);
