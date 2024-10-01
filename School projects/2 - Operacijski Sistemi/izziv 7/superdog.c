//compile with:
//gcc -o superdog superdog.c; sudo chown root:root superdog; sudo chmod ug+s superdog
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int dog(int argc, char** argv) {
    int fd = 1;
    if(argc > 1){
        fd = open(argv[1], O_RDONLY);
    }else{
        fd = open("/etc/shadow", O_RDONLY);
    }
    if(fd == 1)return 1;

    char buf[4096];
    int cnt, count = 0;
    while ( (cnt = read(fd, buf, 4096)) > 0 ) {
    write(1, buf, cnt);
    count += cnt;
    }
    close(fd);
    printf("Št. kopiranih bajtov: %d\n", count);
    return 0;
}

int uids() {
    printf("UID: %d\n", getuid());
    printf("EUID: %d\n", geteuid());
    printf("GID: %d\n", getgid());
    printf("EGID: %d\n", getegid());
    return 0;
}

int main(int argc, char* argv[]){
    if(uids())return 1;

    if(dog(argc, argv))return 1;
    
    return 0;
}