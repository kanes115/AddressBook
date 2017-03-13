#include "basetoTest.c"

int main(int argc, char* argv []){

  FILE *res = openFile();

  runList(res);
  runBintree(res);

}
