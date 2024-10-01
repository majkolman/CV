#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    int zac = getpid();
    int n = 3;
    if(argc >= 2){
        n = atoi(argv[1]);
    }
    int izpis;
    for(int i = 0; i < n; i++){
        int pid = fork();
    }
    printf("i: '%d'\n",getpid()-zac);
    sleep(13);
    return 0;
}
