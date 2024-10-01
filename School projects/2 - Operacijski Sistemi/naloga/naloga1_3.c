#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_TOKENS 100
#define BUFFER_SIZE 100
//globalne tabele
char* tokens[MAX_TOKENS];
int tokenize(char* line);
//globalne spremenljivke
int count = 0;
int debug_level = 0;
char poziv[9] = "mysh";
int return_status = 0;
int stat = 0;
int exit_flag = 0;

//deklaracija funkcij
void do_stuff();
int find_builtin(char* cmd);
int debug(char* arg);
int prompt(char* arg);
int status();
int exit_f(char* status);
int help(char* arg);

//tabela znanih ukazov

typedef struct
{
    char* ime;
    void* funkcija;
    char* opis;   
}ukaz;

#define ST_UKAZOV 5

ukaz ukazi[ST_UKAZOV] = {
    {"debug", &debug, "debugger"},
    {"prompt", &prompt, "prompter"},
    {"status", &status, "status"},
    {"exit", &exit_f, "exit"},
    {"help", &help, "pomoc"},
};

int execute_builtin(ukaz funkcija);
int execute_external(char* ime);

int main(int argc, char const *argv[]){
    int terminal = isatty(0);
    char line[BUFFER_SIZE];
    while(isatty(0)){
        if(fgets(line, MAX_TOKENS, stdin) != NULL) {
            do_stuff(line);
        }
    }
    if(!terminal){
        while(fgets(line, MAX_TOKENS, stdin) != NULL){
            do_stuff(line);
        }
    }
    return 0;
}
void do_stuff(char* line){
    //1.del
    for(int i = 0; i < MAX_TOKENS; i++){
        tokens[i] = NULL;
    }
    int space = 1;
    int comment = 0;
    if(line[0] == '#')comment = 1;
    int printed = 0;
    for(int i = 0; line[i] != '\0'; i++){
        if(line[i] != ' ')space = 0;
        if(line[i] == '\n'){
            line[i] = '\0';
            if(debug_level > 0) printf("Input line: '%s'\n",line);
            line[i] = '\n';
            printed = 1;
        }
    }
    if(!printed)printf("Input line: '%s'\n",line);
    if(!space && !comment) tokenize(line);
    for(int i = 0; i < MAX_TOKENS; i++){
        if(tokens[i] != NULL && debug_level) printf("Token %d: '%s'\n", i, tokens[i]);
    }
    //2.del
    //pogledamo zadnje tri argumente
    char* vhod = 0;
    char* izhod = 0;
    int background = 0;
    int vhod_f = 0;
    int izhod_f = 0;
    //neki
    int minus = 0;
    for(int i = 0; i < 3; i++){
        if(count - i - 1 > 0){
            if(tokens[count - i - 1][0] == '>'){
                izhod = tokens[count - i - 1] + 1;
                izhod_f = 1;
                minus++;
            }
            if(tokens[count - i - 1][0] == '<'){
                vhod = tokens[count - i - 1] + 1;
                vhod_f = 1;
                minus++;
            }   
            if(tokens[count - i - 1][0] == '&'){
                background = 1;
                
                minus++;
            }
        }
    }
    if(vhod_f && debug_level)printf("Input redirect: '%s'\n",vhod);
    if(izhod_f && debug_level)printf("Output redirect: '%s'\n",izhod);
    if(background && debug_level)printf("Background: %d\n", background);
    count -= minus;

    char* cmd = NULL;
    if(count > 0)cmd = tokens[0];

    //poklicemo funkcijo ki skusa najti vgrajeno funkcijo
    if(cmd != NULL) find_builtin(cmd);
}

int tokenize(char* line){
    count = 0;
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
    if(!isspace(line[p - 1]) && !skip && line[p-1] != '\0') {
        tokens[count] = zacetek;
        count++;
    }
    line[p] = '\0';
    return 0;
}
int find_builtin(char* cmd){
    for(int i = 0; i < ST_UKAZOV; i++){
        if(strcmp(cmd, ukazi[i].ime) == 0){
            execute_builtin(ukazi[i]);
            return 0;
        }
    }
    execute_external(cmd);
}

int execute_builtin(ukaz funkcija){
    if(debug_level)printf("Executing builtin '%s' in foreground\n", funkcija.ime);
    char* arg = NULL;
    if(count > 1)arg = tokens[1];

    int (*fun_ptr)(char*) = funkcija.funkcija;
    return_status = (*fun_ptr)(arg);

    return 0;
}

int execute_external(char* ime){
    printf("External command '%s",tokens[0]);
    for(int i = 1; i < count; i++){
        printf(" %s",tokens[i]);
    }
    printf("'\n");
}

int debug(char* arg){
    if(arg == NULL){
        printf("%d\n",debug_level);
        return 0;
    }else{
        debug_level = atoi(arg);
        return 0;
    }
}


int prompt(char* arg){
    if(arg == NULL){
        printf("%s\n",poziv);
        return 0;
    }else{
        int velikost = strlen(arg);
        if(strlen(arg) <= 8){
            for(int i = 0; arg[i] != '\0'; i++){
            poziv[i] = arg[i];
            }
            poziv[velikost] = '\0';
            return 0;
        }else{
            return 1;
        }
    }
}

int status(){
    printf("%d\n",return_status);
    return return_status;
}

int exit_f(char* status){
    stat = return_status;
    if(status != NULL){
        stat = atoi(status);
    }
    //exit_flag = 1;
    exit(stat);
    return 0;
}

int help(char* arg){
    if(arg == NULL){
        printf("\nUkaz: debug level\n\nOpcijski številčni argument level podaja nivo razhroščevanja (debug level).\nČe argument ni podan, se izpiše trenutni nivo razhroščevanja.\nČe pa je podan, se nastavi nivo razhroščevanja na podani level. Če uporabnik poda število v napačni obliki, potem se privzame 0. Glej pomoč za funkcijo atoi().\nIzpise (izpis vhodne vrstice, simbolov in zaznanih posebnosti izvedbe.), ki smo jih že naredili v predhodnih delih, spremenimo tako, da se izpišejo le, če je nivo razhroščevanja večji od 0.\nZačetni nivo razhroščevanja naj bo 0.\nNivoje od 2 in višje lahko uporabljate za svoje potrebe.\n");
        printf("\nUkaz: prompt poziv\n\nS tem ukazovom izpišemo ali nastavimo izpis pozivnika (prompt).\nČe argument ni podan, potem se izpiše trenutni poziv.\nČe je podan, pa se nastavi nov pozivnik. Podano ime lahko vsebuje do 8 znakov, v primeru daljšega imena, se vrne izhodni status 1.\n");
        printf("\nUkaz: status\n\nIzpiše se izhodni status zadnjega izvedenega ukaza.\nTa ukaz izjemoma status pusti nespremenjen.\n");
        printf("\nUkaz: exit status\n\nIzvajanje lupine se zaključi s podanim izhodnim statusom.\nČe argument ni podane, se lupina konča s statusom zadnjega izvedenega ukaza.\n");
        printf("\nUkaz: help\n\nIzpiše spisek podprtih ukazov. Izpis oblikujte po vaši želji - se ne preverja avtomatsko.\n");
        return 0;
    }
    for(int i = 0; i < ST_UKAZOV; i++){
        if(strcmp(arg, ukazi[i].ime) == 0){
            printf("%s\n", ukazi[i].opis);
            return 0;
        }
    }
    return 0;
}
