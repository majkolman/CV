#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int last_child_status = 0;
int energija = 42;
int pike = 1;

void sigterm_handler(int signum) {
	energija += 10;
    printf("Yahoo! Bonus energy (%d).\n",energija);
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
        printf("Child exit with status: %d.\n", izhodni_status);
        exit(izhodni_status);
	} else {
        printf("Child created wtih PID: %d.\n", pid);
    }
}

void zombies(int signum) {
    int status, pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Zombie caught with status %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[]) {
	// V resnici je v Linuxu dovolj takole:
	// signal(SIGCHLD, SIG_IGN);
	// TLPI: Explicitly setting the disposition of SIGCHLD to SIG_IGN causes any child process that subsequently
	// terminates to be immediately removed from the system instead of being converted into a zombie.
    if(argc > 1)energija = atoi(argv[1]);
    printf("My PID: %d\n", getpid());
    printf("Starting with energy: %d\n",energija);

    signal(SIGTERM, sigterm_handler);
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);
    signal(SIGCHLD, zombies);

    while(energija > 0){
        if(pike){
            printf(".");
            fflush(stdout);
        }else{
            printf("*");
            fflush(stdout);
        }
        energija -= 1;
        sleep(1);
    }
    printf("Out of energy. Oooooof.\n");
	return 0;
}
