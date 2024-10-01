#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    int n = 10;
    if(argc >= 2){
        n = atoi(argv[1]);
    }
    

    int pids[n];
    int i;
    /* Start children. */
    for (i = 0; i < n; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            int st_pon = 42/(1+i);
            for(int j = 0; j < st_pon; j++){
                printf("%c\n",'A'+i);
                sleep(1+i);
            }
            exit(i);
        }
    }

    for(int i = 0; i < 10; i++){
        printf("*\n");
        sleep(1);
    }
    //pocakaj na konec otrokov
    for(i=0; i<n; i++){
        //Parent process waits for child process to finish execution
        int status;
        wait(&status);
    }
    //izpisi 
    printf("Samo brez panike\n");
    return 42;

}
