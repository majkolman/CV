#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

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
int stat_my = 0;
int exit_flag = 0;

//deklaracija funkcij
int debug(char* arg);
int prompt(char* arg);
int status();
int exit_f(char* status);
int help(char* arg);
int print();
int echo();
int len();
int sum();
int calc(char* arg1, char* op, char* arg2);
int basename(char* arg);
int dirname(char* arg);
int dirch(char* imenik);
int dirwd(char* mode);
int dirmk(char* imenik);
int dirrm(char* imenik);
int dirls(char* imenik);
//tabela znanih ukazov

typedef struct
{
    char* ime;
    void* funkcija;
    char* opis;   
}ukaz;

#define ST_UKAZOV 17

ukaz ukazi[ST_UKAZOV] = {
    {"debug", &debug, "debugger"},
    {"prompt", &prompt, "prompter"},
    {"status", &status, "status"},
    {"exit", &exit_f, "exit"},
    {"help", &help, "pomoc"},
    {"print", &print, "Ukaz: print args...\n-Izpiše podane argumente na standardni izhod (brez končnega skoka v novo vrstico)."},
    {"echo", &echo, "Ukaz: echo args...\n-Kot ukaz print, le da izpiše še skok v novo vrstico."},
    {"len", &len, "Ukaz: len args...\n-Izpiše skupno dolžino vseh argumentov (kot nizi)"},
    {"sum", &sum, "Ukaz: sum args...\n-Sešteje svoje argumente (cela števila) in izpiše vsoto."},
    {"calc", &calc, "Ukaz: calc arg1 op arg2\n-Nad argumentoma arg1 in arg2 izvede operacijo op in izpiše rezultat.\n-Argumenta sta števili.\n-Operacija je lahko +, -, *, /, %."},
    {"basename", &basename, "Ukaz: basename arg\n-Izpiše osnovno ime podane poti arg, podobno kot ukaz basename.\n-Če argument ni podan, naj bo izhodni status enak 1."},
    {"dirname", &dirname, "Ukaz: dirname arg\n-Izpiše imenik podane poti arg, podobno kot ukaz dirname.\n-Če argument ni podan, naj bo izhodni status enak 1."},
    {"dirch", &dirch, "Ukaz: dirch imenik\n-Zamenjava trenutnega delovnega imenika (working directory).\n-Če imenika ne podamo, naj skoči na korenski imenik."},
    {"dirwd", &dirwd, "Ukaz: dirwd mode\n-Izpis trenutnega delovnega imenika.\n-Če je mode enako full se izpiše celotna pot.\n-Če je mode enako base, se izpiše le osnova imena (basename).\n-Če argumenta ne podamo, se privzame base."},
    {"dirmk", &dirmk, "Ukaz: dirmk imenik\n-Ustvarjanje podanega imenika."},
    {"dirrm", &dirrm, "Ukaz: dirrm imenik\n-Brisanje podanega imenika."},
    {"dirls", &dirls, "Ukaz: dirls imenik\n-Preprost izpis vsebine imenika.\n-Izpišejo se le imena datotek, ločena z dvema presledkoma.\n-Če imena imenika ne podamo, se privzame trenutni delovni imenik."},
};

int execute_builtin(ukaz funkcija);
int execute_external(char* ime);
void process_line();
int parser();
int find_builtin(char* cmd);

int main(int argc, char const *argv[]){
    int terminal = isatty(0);
    char line[BUFFER_SIZE];
    while(isatty(0)){
        if(fgets(line, MAX_TOKENS, stdin) != NULL) {
            process_line(line);
        }
    }
    if(!terminal){
        while(fgets(line, MAX_TOKENS, stdin) != NULL){
            process_line(line);
        }
    }
    return return_status;
}
void clear_tokens(){
    for(int i = 0; i < MAX_TOKENS; i++){
        tokens[i] = NULL;
    }
}
void run_tokenize(char* line){
    clear_tokens();
    int space = 1;
    int tab = 1;
    int comment = 0;
    if(line[0] == '#')comment = 1;
    int printed = 0;
    for(int i = 0; line[i] != '\0'; i++){
        if(line[i] != ' ')space = 0;
        if(line[i] != '\t')tab = 0;
        if(line[i] == '\n'){
            line[i] = '\0';
            if(debug_level > 0) printf("Input line: '%s'\n",line);
            line[i] = '\n';
            printed = 1;
        }
    }
    if(!printed)printf("Input line: '%s'\n",line);
    if(!tab && !space && !comment) tokenize(line);
    for(int i = 0; i < MAX_TOKENS; i++){
        if(tokens[i] != NULL && debug_level) printf("Token %d: '%s'\n", i, tokens[i]);
    }
    fflush(stdout);
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

        if(!narekovaj && (line[p] == ' ' || line[p] == '\t') && !is_space){
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
int parser(){
    char* vhod = 0;
    char* izhod = 0;
    int background = 0;
    int vhod_f = 0;
    int izhod_f = 0;

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
    fflush(stdout);
    count -= minus;
    return 0;
}
void process_line(char* line){
    //1.del
    run_tokenize(line);
    
    //2.del
    if(parser() != 0){
        exit(1);
    }

    char* cmd = NULL;
    if(count > 0)cmd = tokens[0];

    //poklicemo funkcijo ki skusa najti vgrajeno funkcijo
    if(cmd != NULL) find_builtin(cmd);
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
    if(debug_level){
        printf("Executing builtin '%s' in foreground\n", funkcija.ime);
        fflush(stdout);
    }

    int MAX_ARGS = 3;
    char* args[MAX_ARGS];
    for(int i = 0; i < MAX_ARGS; i++){
        args[i] = NULL;
    }
    
    if(count > 1){
        for(int i = 1; i < count && i <= MAX_ARGS; i++){
            args[i-1] = tokens[i]; 
        }
    }
    int (*fun_ptr)() = funkcija.funkcija;
    return_status = (*fun_ptr)(args[0],args[1],args[2]);

    return 0;
}

int execute_external(char* ime){
    printf("External command '%s",tokens[0]);
    for(int i = 1; i < count; i++){
        printf(" %s",tokens[i]);
        fflush(stdout);
    }
    printf("'\n");
    fflush(stdout);
}

int debug(char* arg){
    if(arg == NULL){
        printf("%d\n",debug_level);
        fflush(stdout);
        return 0;
    }else{
        debug_level = atoi(arg);
        return 0;
    }
}


int prompt(char* arg){
    if(arg == NULL){
        printf("%s\n",poziv);
        fflush(stdout);
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
    fflush(stdout);
    return return_status;
}

int exit_f(char* status){
    stat_my = return_status;
    if(status != NULL){
        stat_my = atoi(status);
    }
    //exit_flag = 1;
    exit(stat_my);
    return 0;
}

int help(char* arg){
    if(arg == NULL){
        printf("razpolozljivi vgrajeni ukazi so:\n");
        for(int i = 0; i < ST_UKAZOV; i++){
            printf("'%s' ", ukazi[i].ime);
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
        return 0;
    }
    for(int i = 0; i < ST_UKAZOV; i++){
        if(strcmp(arg, ukazi[i].ime) == 0){
            printf("%s\n", ukazi[i].opis);
            fflush(stdout);
            return 0;
        }
    }
    return 0;
}

int print(){
    if(count > 1){
        for(int i = 1; i < count - 1; i++){
            printf("%s ", tokens[i]); 
            fflush(stdout);
        }
        printf("%s", tokens[count-1]); 
        fflush(stdout);
    }
    //printf("\n");
    return 0;
}

int echo(){
    if(count > 1){
        for(int i = 1; i < count - 1; i++){
            printf("%s ", tokens[i]); 
            fflush(stdout);
        }
        printf("%s ", tokens[count-1]); 
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
    return 0;
}

int len(){
    int counter = 0;
    if(count > 1){
        for(int i = 1; i < count; i++){
            for(int j = 0; tokens[i][j] != '\0'; j++){
                counter++;
            }
        }
    }
    printf("%d\n", counter);
    fflush(stdout);
    return 0;
}

int sum(){
    int sum = 0;
    if(count > 1){
        for(int i = 1; i < count; i++){
            sum += atoi(tokens[i]);
        }
    }
    printf("%d\n", sum);
    fflush(stdout);
    return 0;
}

int calc(char* arg1, char* op, char* arg2){
    if(arg1 == NULL || op == NULL || arg2 == NULL){
        return 1;
    }
    int a1 = atoi(arg1);
    int a2 = atoi(arg2);
    int res = 0;
    switch (op[0])
    {
    case '+':
        res = a1 + a2;
        break;
    case '-':
        res = a1 - a2;
        break;
    case '*':
        res = a1 * a2;
        break;
    case '/':
        res = a1 / a2;
        break;
    case '%':
        res = a1 % a2;
        break;
    default:
        perror("calc");
        return 1;
        break;
    }
    printf("%d\n",res);
    fflush(stdout);
    return 0;
}

int basename(char* arg){
    if(arg == NULL){
        return 1;
    }
    
    char* p = arg;
    char* return_string = p;
    int next = 0;
    while(*p != '\0'){
        if(*p == '/')return_string = p+1;
        p++;
    }
    printf("%s\n",return_string);
    fflush(stdout);
    return 0;
}

int dirname(char* arg){
    if(arg == NULL){
        return 1;
    }
    
    char* p = arg;
    char* konec = p;
    int next = 0;
    while(*p != '\0'){
        if(*p == '/')konec = p;
        p++;
    }
    *konec = '\0';

    printf("%s\n",arg);
    fflush(stdout);
    return 0;
}

int dirch(char* imenik){
    int return_val = 0;
    if(imenik == NULL){
        return_val = chdir("/");
    }else{
        return_val = chdir(imenik);
    }
    if(return_val){
        int error = errno;
        perror("dirch");
        fflush(stderr);
        return error;
    }
    return 0;
}

int dirwd(char* mode){
    char* dir = malloc(100*sizeof(char));
    
    if(getcwd(dir, 100) == NULL){
        int error = errno;
        perror("getcwd");
        fflush(stderr);
        free(dir);
        return error;
    }

    if(mode == NULL){
        if(!strcmp(dir, "/")){
            printf("%s\n",dir);
            fflush(stdout);
        }
        else basename(dir);
        free(dir);
        return 0;
    }
    if(!strcmp(mode, "full")){
        printf("%s\n",dir);
        fflush(stdout);
    }else if(!strcmp(mode, "base")){
        if(!strcmp(dir, "/")){
            printf("%s\n",dir);
            fflush(stdout);
        }
        else basename(dir);
    }else{
        int error = errno;
        perror("dirwd");
        fflush(stderr);
        free(dir);
        return error;
    }
    free(dir);
    return 0;
}

int dirmk(char* imenik){
    int return_val = 0;
    if(imenik == NULL){
        return 1;
    }else{
        return_val = mkdir(imenik, 0777);
    }
    if(return_val){
        int error = errno;
        perror("dirmk");
        fflush(stderr);
        return error;
    }
    return 0;
}

int dirrm(char* imenik){
    int return_val = 0;
    if(imenik == NULL){
        return_val = rmdir(imenik);
    }else{
        return_val = rmdir(imenik);
    }
    if(return_val){
        int error = errno;
        perror("dirrm");
        fflush(stderr);
        return error;
    }
    return 0;
}

int dirls(char* imenik){
    if(imenik == NULL){
        imenik = ".";
    }
    struct dirent *de;
    DIR *d;
    d = opendir(imenik);
    if(d == NULL){
        int error = errno;
        perror("dirls");
        fflush(stderr);
        return error;
    }else if(d){
        while((de = readdir(d)) != NULL){
            printf("%s  ",de->d_name);
            fflush(stdout);
        } 
        printf("\n");
        fflush(stdout);
        closedir(d);
        return 0;
    }
    return 1;
}
