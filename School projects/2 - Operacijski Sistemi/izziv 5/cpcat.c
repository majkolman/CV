#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

void izpis(int fd1, int fd2);

int main(int argc, char const *argv[])
{
    //printf("%d\n", argc);

    char const* vhod;
    char const* izhod;

    if(argc == 1){
        //stdin -> stdout
        //vhod = stdin;
        //izhod = stdout;
        
        izpis(0, 1);
    }else if(argc == 2){
        //izpis datoteke
        vhod = argv[1];
        //izhod = stdout;

        int fd1 = open(vhod, O_RDONLY);

        izpis(fd1, 1);
        close(fd1);
    }else if(argc == 3 && argv[1][0] == '-'){
        //stdin -> datoteka
        //vhod = stdin;
        izhod = argv[2];

        int fd2 = open(izhod, O_RDWR | O_CREAT | O_TRUNC, 0644);

        izpis(0, fd2);
        close(fd2); 
    }else if(argc == 3){
        //dat -> dat
        vhod = argv[1];
        izhod = argv[2];
        
        int fd1 = open(vhod, O_RDONLY);
        int fd2 = open(izhod, O_RDWR | O_CREAT | O_TRUNC, 0644);

        izpis(fd1, fd2);
        close(fd1);
        close(fd2); 
    }else{
        perror("wrong arguments");
        exit(1);
    }
    return 0;
}
void izpis(int fd1, int fd2){
    if (fd1 < 0) 
    { 
        perror("vhod"); 
        exit(1); 
    }
    if (fd2 < 0) 
    { 
        perror("izhod"); 
        exit(1); 
    }  
    char* buffer = malloc(sizeof(char*) * 100);
    while(read(fd1, buffer, 1) > 0){
            write(fd2, buffer, 1);
    }
}
