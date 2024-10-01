#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int last_child_status = 0;
int energija = 42;
int pike = 1;
FILE* fd;
time_t ltime;

void printtimestamp(){
    ltime = time(NULL);
    char* time = asctime(localtime(&ltime));
    time[strlen(time) - 1] = '\0';
    fprintf(fd, "%s: ",time);
}

void sigterm_handler(int signum) {
	energija += 10;
    printtimestamp();
    fprintf(fd, "Yahoo! Bonus energy (%d).\n",energija);
    fflush(fd);
}

void sigusr1_handler(int signum) {
	if(pike) pike = 0;
    else pike = 1;
}

void sigusr2_handler(int signum) {
	int pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(1);
	}
	if (pid == 0) {
		sleep((energija % 7) + 1);
        int izhodni_status = (42 * energija) % 128;
        printtimestamp();
        fprintf(fd, "Child exit with status: %d.\n", izhodni_status);
        fflush(fd);
        exit(izhodni_status);
	} else {
        printtimestamp();
        fprintf(fd, "Child created wtih PID: %d.\n", pid);
        fflush(fd);
    }
}

void zombies(int signum) {
    int status, pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printtimestamp();
        fprintf(fd, "Zombie caught with status %d\n", WEXITSTATUS(status));
        fflush(fd);
    }
}

int main(int argc, char *argv[]) {
	// V resnici je v Linuxu dovolj takole:
	// signal(SIGCHLD, SIG_IGN);
	// TLPI: Explicitly setting the disposition of SIGCHLD to SIG_IGN causes any child process that subsequently
	// terminates to be immediately removed from the system instead of being converted into a zombie.
    if(!fork()){
        fd = fopen("demonski_lovec.log", "w");

        if(argc > 1)energija = atoi(argv[1]);
        printtimestamp();
        fprintf(fd ,"My PID: %d\n", getpid());
        fflush(fd);
        printtimestamp();
        fprintf(fd ,"Starting with energy: %d\n",energija);
        fflush(fd);

        signal(SIGTERM, sigterm_handler);
        signal(SIGUSR1, sigusr1_handler);
        signal(SIGUSR2, sigusr2_handler);
        signal(SIGCHLD, zombies);

        while(energija > 0){
            if(pike){
                printtimestamp();
                fprintf(fd, ".\n");
                fflush(fd);
            }else{
                printtimestamp();
                fprintf(fd, "*\n");
                fflush(fd);
            }
            energija -= 1;
            sleep(1);
        }
        printtimestamp();
        fprintf(fd, "Out of energy. Oooooof.\n");
        fflush(fd);
        return 0;
    }
}

