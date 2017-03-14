#include <time.h>
#include <ctype.h>
#include <sys/time.h>

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


FILE* openFile(){
  FILE *resultsF = fopen("scores.txt", "ab+");

  if(resultsF == NULL){
    printf("Error opening file!\n");
    exit(1);
  }

  return resultsF;
}


struct rusage rusage_start,rusage_end;
struct timeval user_start,user_end,system_start,system_end,real_start,real_end;

void start_clock(){
  getrusage(RUSAGE_SELF,&rusage_start);
  gettimeofday(&real_start,NULL);
}
double end_clock(FILE* file){
  gettimeofday(&real_end,NULL);
  getrusage(RUSAGE_SELF,&rusage_end);

  user_start=rusage_start.ru_utime; //sekundy i mikrosekundy (sek - tv_sec, mikrosek - tv_usec)
  user_end=rusage_end.ru_utime;
  system_start=rusage_start.ru_stime;
  system_end=rusage_end.ru_stime;

  fprintf(file, "\tsystem time %09ld microseconds\n",((system_end.tv_sec - system_start.tv_sec)*1000000L) + system_end.tv_usec - system_start.tv_usec);//zamiana na mikrosekundy
  fprintf(file, "\tuser time %09ld microseconds\n",((user_end.tv_sec - user_start.tv_sec)*1000000L+ user_end.tv_usec) - user_start.tv_usec);
  fprintf(file, "\treal time %09ld microseconds\n",((real_end.tv_sec - real_start.tv_sec)*1000000L + real_end.tv_usec) - real_start.tv_usec);

  return ((real_end.tv_sec - real_start.tv_sec)*1000000L + real_end.tv_usec) - real_start.tv_usec;
}

int numbers_only(const char *s){
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }

    return 1;
}
