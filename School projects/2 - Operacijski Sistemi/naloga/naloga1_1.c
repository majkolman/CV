#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_TOKENS 100
#define BUFFER_SIZE 100
char* tokens[MAX_TOKENS];
int tokenize(char* line);
void do_stuff();

int main(int argc, char const *argv[]){
    int terminal = isatty(0);
    char line[BUFFER_SIZE];
    while(isatty(0)){
        fgets(line, MAX_TOKENS, stdin);
        do_stuff(line);
    }
    if(!terminal){
        while(fgets(line, sizeof line, stdin) != NULL){
            do_stuff(line);
        }
    }
    return 0;
}
void do_stuff(char* line){
    int space = 1;
    int comment = 0;
    if(line[0] == '#')comment = 1;
    int printed = 0;
    for(int i = 0; line[i] != '\0'; i++){
        if(line[i] != ' ')space = 0;
        if(line[i] == '\n'){
            line[i] = '\0';
            printf("Input line: '%s'\n",line);
            line[i] = '\n';
            printed = 1;
        }
    }
    if(!printed)printf("Input line: '%s'\n",line);
    if(!space && !comment) tokenize(line);
    for(int i = 0; i < MAX_TOKENS; i++){
        if(tokens[i] != NULL)printf("Token %d: '%s'\n", i, tokens[i]);
    }
}

int tokenize(char* line){
    for(int i = 0; i < MAX_TOKENS; i++){
        tokens[i] = NULL;
    }
    int count = 0;
    int p = 0;
    int is_space = 0;
    if(isspace(line[0]))is_space = 1;
    int skip = 0;
    if(line[0] == '\n')skip = 1;
    int narekovaj = 0;
    int updated = 0;

    char* zacetek = line;
    while(line[p] != '\n' && !skip){
        if(line[p] == '"'){
            if(narekovaj){
                tokens[count] = zacetek;
                count++;
                line[p] = '\0';
                updated = 1;
            }
            else{
                p++;
                zacetek = line + p;
                narekovaj = 1;
            }
        }
        if(!narekovaj && is_space){
            if(line[p] == '#')skip = 1;
        }

        if(!narekovaj && line[p] == ' ' && !is_space){
            is_space = 1;
            tokens[count] = zacetek;
            count++;
            line[p] = '\0';
        }
        else if(!narekovaj && is_space && line[p] != ' '){
            zacetek = line + p;
            is_space = 0;
        }

        if(updated){
            narekovaj=0;
            updated=0;
        }
        p++;
    }
    if(!isspace(line[p - 1]) && !skip && line[p-1] != '\0') tokens[count] = zacetek;
    line[p] = '\0';
    return 0;
}