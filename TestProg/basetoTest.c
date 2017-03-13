#include <time.h>

char *randstring(int length) {
    static int mySeed = 25011984;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    size_t stringLen = strlen(string);
    char *randomString = NULL;

    srand(time(NULL) * length + ++mySeed);

    if (length < 1) {
        length = 1;
    }

    randomString = malloc(sizeof(char) * (length +1));

    if (randomString) {
        short key = 0;

        for (int n = 0;n < length;n++) {
            key = rand() % stringLen;
            randomString[n] = string[key];
        }

        randomString[length] = '\0';

        return randomString;
    }
    else {
        printf("No memory");
        exit(1);
    }
}


double timeElapsed(clock_t start, clock_t end){
  return ((double) (end - start)) / CLOCKS_PER_SEC;
}


FILE* openFile(){
  FILE *resultsF = fopen("scores.txt", "ab+");

  if(resultsF == NULL){
    printf("Error opening file!\n");
    exit(1);
  }

  return resultsF;
}
