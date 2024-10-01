#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <fcntl.h>

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
char proc_status[BUFFER_SIZE] = "/proc";

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
int my_rename(char* izvor, char* ponor);
int my_unlink(char* ime);
int my_remove(char* ime);
int linkhard(char* cilj, char* ime);
int linksoft(char* cilj, char* ime);
int linkread(char* ime);
int linklist(char* ime);
int cpcat(char* izvor, char* ponor);
int pid();
int ppid();
int uid();
int euid();
int gid();
int egid();
int sysinfo();
int proc(char* pot);
int pids();
int pinfo();
//tabela znanih ukazov
typedef struct
{
    char* ime;
    void* funkcija;
    char* opis;   
}ukaz;

#define ST_UKAZOV 35

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
    {"rename", &my_rename, "Ukaz: rename izvor ponor\n-Preimenovanje datoteke izvor v ponor."},
    {"unlink", &my_unlink, "Ukaz: unlink ime\n-Odstrani datoteko s podanim imenom.\n-Natančneje: odstrani le imeniški vnos s podanim imenom.\n-Gre za sistemski klic unlink()."},
    {"remove", &my_remove, "Ukaz: remove ime\n-Odstranjevanje datoteke ali imenika s podanim imenom.\n-Gre za sistemski klic remove()."},
    {"linkhard", &linkhard, "Ukaz: linkhard cilj ime\n-Ustvari trdo povezavo s podanim imenom na cilj."},
    {"linksoft", &linksoft, "Ukaz: linksoft cilj ime\n-Ustvari simbolično povezavo s podanim imenom na cilj."},
    {"linkread", &linkread, "Ukaz: linkread ime\n-Izpiše cilj podane simbolične povezave."},
    {"linklist", &linklist, "Ukaz: linklist ime\n-V trenutnem delovnem imeniku poišče vse trde povezave na datoteko s podanim imenom.\n-Povezave se izpišejo ločene z dvema presledkoma."},
    {"cpcat", &cpcat, "Ukaz: cpcat izvor ponor\n-Znana ukaza cp in cat združena v enega (glej izziv cpcat.c)."},
    {"pid", &pid, "Ukaz: pid\n-Izpis PID procesa lupine"},
    {"ppid", &ppid, "Ukaz: ppid\n-Izpis PID starševskega procesa lupine."},
    {"uid", &uid, "Ukaz: uid\n-Izpis UID uporabnika, ki je lastnik procesa lupine"},
    {"euid", &euid, "Ukaz: euid\n-Izpis UID uporabnika, ki je aktualni lastnik procesa lupine"},
    {"gid", &gid, "Ukaz: gid\n-Izpis GID skupine, kateri pripada proces lupine"},
    {"egid", &egid, "Ukaz: egid\n-Izpis GID skupine, kateri aktualno pripada proces lupine"},
    {"sysinfo", &sysinfo, "Ukaz: sysinfo\n-Izpiše osnovne informacije v sistemu.\n-Uporabite sistemski klic uname().\n-Izpišite polja: sysname, nodename, release, version, machine."},
    {"proc", &proc, "Ukaz: proc pot\n-Nastavitev poti do procfs datotečnega sistema.\n-Brez argumenta se izpiše trenutna nastavitev. Privzeta nastavitev je /proc.\n-Če pa podamo argument, se nastavi nova pot do imenika, ki vsebuje procfs.\n-Pred nastavitvijo poti ta ukaz tudi preveri ali podana pot dejansko obstaja.\n-Če ne obstaja, se pot ne nastavi in vrne izhodni status 1.\n-Za preverjanje poti lahko uporabite funkcijo access(..., F_OK|R_OK)."},
    {"pids", &pids, "Ukaz: pids\n-Izpiše PIDe trenutnih procesov, ki jih pridobi iz procfs.\n-Vsak pid je izpisan v svoji vrstici."},
    {"pinfo", &pinfo, "Ukaz: pinfo\n-Izpiše informacije o trenutnih procesih (PID, PPID, STANJE, IME), ki jih pridobi iz datoteke stat v procfs.\n-Za formatiranje izpisa uporabite naslednji format:\n-printf(\"%5s %5s %6s %s\\n\", \"PID\", \"PPID\", \"STANJE\", \"IME\");"},
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
    clear_tokens();
    count = 0;
    int p = 0;
    int is_space = 0;
    if(isspace(line[0]))is_space = 1;
    int skip = 0;
    if(line[0] == '\n')skip = 1;
    int narekovaj = 0;
    int updated = 0;
    char* zacetek = line;
    while(line[p] != '\n' && line[p] != '\0' && !skip){
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

int my_rename(char* izvor, char* ponor){
    return rename(izvor, ponor);
}

int my_unlink(char* ime){
    return unlink(ime);
}

int my_remove(char* ime){
    return remove(ime);
}

int linkhard(char* cilj, char* ime){
    return link(cilj, ime);
}

int linksoft(char* cilj, char* ime){
    return symlink(cilj, ime);
}

int linkread(char* ime){
    char buf[1024];
    int len = readlink(ime, buf, sizeof(buf)-1);
    if(len != -1){
        buf[len] = '\0';
        printf("%s\n",buf);
        fflush(stdout);
        return 0;
    }
    return 1;
}

int linklist(char* ime){
    struct stat dir;
    if(stat(ime, &dir) < 0){
        int err = errno;
        perror("linklist");
        fflush(stderr);
        return err;
    }
    int file_no = dir.st_ino;

    struct dirent *de;
    DIR *d;
    d = opendir(".");
    if(d == NULL){
        int error = errno;
        perror("linklist");
        fflush(stderr);
        return error;
    }else if(d){
        while((de = readdir(d)) != NULL){
            struct stat s;
            int result = stat(de->d_name, &s);
            if(s.st_ino == file_no){
                printf("%s  ",de->d_name);
                fflush(stdin);
            }
        } 
        printf("\n");
        fflush(stdout);
        closedir(d);
        return 0;
    }
    return 1;
}

int cpcat(char* izvor, char* ponor){
    int fd1 = 0;
    int fd2 = 1;
    
    if(izvor == NULL && ponor == NULL){
        //oba prazna
        int err = errno;
        perror("cpcat");
        fflush(stderr);
        return err;
    }else if(ponor == NULL){
        //samo ponor prazen
        fd1 = open(izvor, O_RDONLY);
    }else{
        //oba neprazna
        fd1 = open(izvor, O_RDONLY);
        fd2 = open(ponor, O_RDWR | O_CREAT | O_TRUNC, 0644);
    }
    if(fd1 < 0 || fd2 < 0) { 
        int err = errno;
        perror("cpcat"); 
        fflush(stderr);
        return err; 
    } 
    char* buffer = malloc(sizeof(char*) * 100);
    while(read(fd1, buffer, 1) > 0){
        write(fd2, buffer, 1);
    }
    if(fd1 != 0)close(fd1);
    if(fd2 != 1)close(fd2);
    return 0;
}
int pid(){
    printf("%d\n",getpid());
    fflush(stdout);
    return 0;
}
int ppid(){
    printf("%d\n",getppid());
    fflush(stdout);
    return 0;
}
int uid(){
    printf("%d\n",getuid());
    fflush(stdout);
    return 0;
}
int euid(){
    printf("%d\n",geteuid());
    fflush(stdout);
    return 0;
}
int gid(){
    printf("%d\n", getgid());
    fflush(stdout);
    return 0;
}
int egid(){
    printf("%d\n", getegid());
    fflush(stdout);
    return 0;
}
int sysinfo(){
    struct utsname buf;
    uname(&buf);
    
    printf("Sysname: %s\n", buf.sysname);
    printf("Nodename: %s\n", buf.nodename);
    printf("Release: %s\n", buf.release);
    printf("Version: %s\n", buf.version);
    printf("Machine: %s\n", buf.machine);
    fflush(stdout);
    return 0;
}
int proc(char* pot){
    if(pot != NULL){
        //try to assign ti proc status
        if(opendir(pot)){
            int exists = 1;
            for(int i = 0; i < BUFFER_SIZE; i++){
                if(exists){
                    proc_status[i] = pot[i];
                    if(pot[i] == '\0')exists = 0;
                }else{
                    proc_status[i] = 0;
                }
            }
        }else{
            return 1;
        }

    }else{
        printf("%s\n",proc_status);
        fflush(stdout);
    }
    return 0;
}
int compare_pids(const void* a, const void* b){
    int inta = 0;
    char *p =(char*) a;
    while(*p != '\0'){
        inta *= 10;
        inta += (*p - '0');
        p++;
    }
    int intb = 0;
    p =(char*) b;
    while(*p != '\0'){
        intb *= 10;
        intb += (*p - '0');
        p++;
    }
    return inta - intb;
}
void sort_pids(char** table, int size){
    int check;
    
    for(int i = 0; i < size - 1; i++){
        check = 0;
        for(int j = 0; j < size - i - 1; j++){
            if(atoi(table[j]) > atoi(table[j+1])){
                
                char* temp = table[j+1];
                table[j+1] = table[j];
                table[j] = temp;
                check = 1;
            } 
        }
        if(!check){
            break;
        }
    }
}
int pids(){
    //opendir proc_status
    //izpise stevilke
    struct dirent *de;
    DIR *d;
    d = opendir(proc_status);
    char* table[100];
    int i = 0;
    if(d == NULL){
        int error = errno;
        perror("pids");
        fflush(stderr);
        return error;
    }else if(d){
        while((de = readdir(d)) != NULL){
            if(atoi(de->d_name) != 0 || de->d_name == "0"){
                table[i++] = de->d_name;
            }
        } 
        //print
        sort_pids(table, i);
        for(int j = 0; j < i; j++){
        printf("%s\n",table[j]);
    }
        fflush(stdout);
        closedir(d);
        return 0;
    }
    return 1;
}
int pinfo(){
    struct dirent *de;
    DIR *d;
    d = opendir(proc_status);
    char* table[100];
    struct dirent *dtable[100];
    int i = 0;
    if(d == NULL){
        int error = errno;
        perror("pids");
        fflush(stderr);
        return error;
    }else if(d){
        while((de = readdir(d)) != NULL){
            if(atoi(de->d_name) != 0 || de->d_name == "0"){
                dtable[i] = de;
                table[i++] = de->d_name;
            }
        } 
        //print
        sort_pids(table, i);
        char ppids[i][BUFFER_SIZE];
        char stanja[i][BUFFER_SIZE];
        char imena[i][BUFFER_SIZE];
        //for every pid
        for(int j = 0; j < i; j++){
            //get path of stat
            char path[200];
            snprintf(path, sizeof(path), "%s/%s/stat", proc_status, table[j]);
            //open stat
            int fd = open(path, O_RDONLY);
            if(fd < 0) { 
                int err = errno;
                perror("pinfo"); 
                fflush(stderr);
                return err; 
            } 
            //read from stat
            char buffer[BUFFER_SIZE];
            int count = read(fd, buffer, sizeof(buffer) - 1);
            if(count < 0){
                int err = errno;
                perror("pinfo"); 
                fflush(stderr);
                return err; 
            }
            buffer[count] = '\0';
            //read from buffer
            char* p = buffer;
            int oklepaj = 0;
            tokenize(buffer);
            fflush(stdout);
            for(int y = 1; y < 4; y++){
                    int check = 1;
                    for(int x = 0; x < BUFFER_SIZE - 1; x++){
                        if(y == 1){
                            if(check && !isspace(tokens[1][x])){
                                if(tokens[1][x] == '('){
                                    oklepaj += 1;
                                    if(oklepaj == 1) x++;
                                }
                                if(tokens[1][x] == ')'){
                                    oklepaj -= 1;
                                    if(oklepaj == 0) x++;
                                }
                                imena[j][x-1] = tokens[1][x];
                            }else{
                                check = 0;
                            }  
                        }else if(y == 2){
                            if(check && !isspace(tokens[2][x])){
                                stanja[j][x] = tokens[2][x];
                            }else{
                                check = 0;
                            }  
                        }else if(y == 3){
                            if(check && !isspace(tokens[3][x])){
                                ppids[j][x] = tokens[3][x];
                            }else{
                                check = 0;
                            }  
                        } 
                    }
            }
            close(fd);
        }
        printf("%5s %5s %6s %s\n", "PID", "PPID", "STANJE", "IME");
        fflush(stdout);
        for(int j = 0; j < i; j++){
            printf("%5s %5s %6s %s\n", table[j], ppids[j], stanja[j], imena[j]);
            fflush(stdout);
        }
        fflush(stdout);
        closedir(d);
        return 0;
    }
    return 1;
}