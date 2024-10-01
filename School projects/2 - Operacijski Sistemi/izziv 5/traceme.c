#include <stdio.h>

int main(){

    fprintf(stdout, "%s", "Juhuhu, pomlad je tu.\n");     // "Hello world" on stdout (using fprintf)
    fprintf(stderr, "%s", "Stack overflow!\n");
    return 42;
}