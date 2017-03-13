#include <dlfcn.h>

typedef struct functions{

}funcs;



int main(int argc, char* argv []){

  void* handle;

  handle = dlopen("../libAddressBook.so", RTLD_LAZY);

  if (!handle){
    fprintf(stderr, "%s\n", dlerror());
    return 1;
  }

  Book_bin* (*createEmptyAddBook_bin)(ORGANIZED_BY);

  createEmptyAddBook_bin = dlsym(handle, "createEmptyAddBook_bin");

  error = dlerror();
   if (error != NULL) {
     fprintf(stderr, "%s\n", error);
     return 1;
    }

  Book_bin* res = (*createEmptyAddBook_bin)(0);

  dlclose(handle);


}
