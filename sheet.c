/**
 * @Author: Vojtěch Kališ, (xkalis03@stud.fit.vutbr.cz)
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100
#define MAX_ROW_LENGTH 10242

/** TODO:

SYNTAX SPOUSTENI~
Uprava velikosti tabulky:
./sheet [-d DELIM] [Prikazy pro upravu tabulky]
nebo zpracovani dat:
./sheet [-d DELIM] [Selekce radku] [Prikaz pro zpracovani dat]

Argument -d specifikuje, jake znaky lze interpretovat jako oddelovace jednotlivych bunek. Kazdy znak ve vstupnim radku, ktery je obsazen v retezci DELIM, 
se chova jako oddelovac dvou sousedicich bunek. Ve vychozim nastaveni je DELIM retezec obsahujici mezeru. Vicenasobny vyskyt stejnych znaku v retezci DELIM je 
ignorovan. Prvni znak z retezce DELIM bude take pouzit jako oddelovac vystupnich hodnot.

==================
  Uprava tabulky
==================

Prikazu pro upravu tabulky muze byt zadano vice. V takovem pripade budou zadany jako sekvence vice argumentu prikazove radky:

Prikazy pro upravu tabulky:

irow R - vlozi radek tabulky pred radek R > 0 (insert-row).
arow - prida novy radek tabulky na konec tabulky (append-row).
drow R - odstrani radek cislo R > 0 (delete-row).
drows N M - odstrani radky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N.
icol C - vlozi prazdny sloupec pred sloupec dany cislem C.
acol - prida prazdny sloupec za posledni sloupec.
dcol C - odstrani sloupec cislo C.
dcols N M - odstrani sloupce N az M (N <= M). V pripade N=M se prikaz chova stejne jako dcol N.

==================
  Zpracovani dat
==================

Zpracovanu dat predstavuje upravy obsahu jednotlivych bunek tabulky. Kazde spusteni programu muze obsahovat nejvice jeden prikaz pro zpracovani dat. 

Prikazy pro zpracovani dat:

Prikazy, ktere jsou povinne pro uspesne splneni projektu:
cset C STR - do buňky ve sloupci C bude nastaven retezec STR.
tolower C - retezec ve sloupci C bude preveden na mala pismena.
toupper C - retezec ve sloupce C bude preveden na velka pismena.
round C - ve sloupci C zaokrouhli cislo na cele cislo.
int C - odstrani desetinnou cast cisla ve sloupci C.
copy N M - prepise obsah bunek ve sloupci M hodnotami ze sloupce N.
swap N M - zameni hodnoty bunek ve sloupcich N a M.
move N M - presune sloupec N před sloupec M.

Prikazy, ktere jsou volitelne pro uspesne splneni projektu:
csum C N M - do bunky ve sloupci C bude ulozeno cislo reprezentujici soucet hodnot bunek na stejnem radku ve sloupcich N az M vcetne (N <= M, C nesmi patrit do intervalu <N;M>).
cavg C N M - obdobne jako csum, avsak vysledna hodnota predstavuje aritmeticky prumer hodnot.
cmin C N M - obdobne jako csum, avsak vysledna hodnota predstavuje nejmensi nalezenou hodnotu.
cmax C N M - obdobne jako cmin, jedna se vsak o maximalni nalezenou hodnotu.
ccount C N M - obdobne jako csum, avsak vysledna hodnota predstavuje pocet neprazdnych hodnot danych bunek.
cseq N M B - do bunek ve sloupcich N az M vcetne vlozi postupne rostouci cisla (o jednicku) pocinaje hodnotou B.
rseq C N M B - ve sloupci C do bunek kazdeho radku od radku N po radek M vcetne vlozi rostouci cisla pocinaje hodnotou B. Cislo M může byt nahrazeno pomlckou. V takovem pripade se tim mysli posledni radek souboru.
rsum C N M - do bunky ve sloupci C na radku M+1 vlozi soucet hodnot bunek ve sloupci C na radcich N az M vcetne.
ravg C N M - obdobne jako rsum, avsak vysledna hodnota predstavuje aritmeticky prumer.
rmin C N M - obdobne jako rsum, avsak vysledna hodnota predstavuje nejmensi hodnotu.
rmax C N M - obdobne jako rsum, avsak vysledna hodnota predstavuje nejvetsi hodnotu.
rcount C N M - obdobne jako rsum, avsak vysledna hodnota predstavuje pocet neprazdnych hodnot danych bunek.

**/

/**     LORD GIVE ME THE MENTAL CAPACITY TO REMEMBER THESE, but in the meantime, this cheatsheet should suffice.
GitHub push flow:   $ git add .
                    $ git commit -m "message"
                    $ git push --set-upstream origin main   (where 'main' is name of branch to commit to)

!!!(Forces local file overwrite)!!!
GitHub pull flow:   $ git fetch origin main
                    $ git reset --hard origin/main

VSCode Keybind-sheet:  CTRL+SHIFT+B -> BUILD
                        F5 -> DEBUG
**/


/** V zadanem retezci prevedte mala pismena na velka
    int diff = 'a' - 'A';

    int i = 0;
    while (str[i] != '\0'){
        if (str[i] >= 'a' && str[i] <= 'z'){
            str[i] = str[i] - diff;
        }
        i++;
    }
**/


/**
 * [STRUCTURES]
**/
typedef struct {
    bool rowsel;
    bool rows;
    bool beginswith;
    bool contains;
    //bool acol;
    bool argcheck;
} flags_t;


/**
 * [AUXILIARY] FUNCTIONS
**/
int calc_cols(char* row, char* delim){
    int tmp = 1;
    for (int i = 0; row[i] != '\0'; i++){
        for (int j = 0; delim[j] != '\0'; j++){
            if (row[i] == delim[j]){
                tmp++;
            }
        }
    }
    return tmp;
}

void print_stdin(char* row){
    printf("%s",row);
}

void check_rowselect(int i, char *argv[], flags_t* flags, int* to, int* from, int* col, char str[], int* str_len){
    if (strcmp(argv[i], "rows") == 0){
        flags->rows = true;
        flags->rowsel = true;
        *from = atoi(argv[i+1]);
        *to = atoi(argv[i+2]);
    } else if (strcmp(argv[i], "beginswith") == 0){
        flags->beginswith = true;
        flags->rowsel = true;
        *col = atoi(argv[i+1]);
        strcpy(&str[0], argv[i+2]);
        *str_len = strlen(str);
        printf("str_len = %d\n",*str_len);
    } else if (strcmp(argv[i], "contains") == 0){
        flags->contains = true;
        flags->rowsel = true;
        *col = atoi(argv[i+1]);
        strcpy(&str[0], argv[i+2]);
        *str_len = strlen(str);
    }
}

int rowsel(char* row, int curr_row, int from, int to, flags_t* flags, int col, char* str, char* delim, int str_len){
    //ROWS
    if(flags->rows == true){
        if(curr_row < from || curr_row > to){
            return 0;
        }
        return 1;        
    }
    //BEGINSWITH
    if(flags->beginswith == true){
        int tmp1 = 1;
        int i = 0;
        if (tmp1 == col){
            if(row[i] != str[i]){
                return 0; //WE DIDN'T WIN
            } else {
                int tmp = 1;
                for(int k = 0; str[k] != '\0'; k++){
                    if(row[tmp] == str[k]){
                        tmp++;
                        continue;
                    } else {
                        return 0;
                    }
                    if(tmp == str_len){
                        return 1; //WE WON
                    }
                }
            }
        }
        while(row[i] != '\0'){
            for (int j = 0; delim[j] != '\0'; j++){
                if (row[i] == delim[j]){ //encounter a delimiter
                    tmp1++;
                    if(tmp1 == col){
                        int tmp2 = i;
                        int cnt = 0;
                        ++tmp2;
                        for(int k = 0; str[k] != '\0'; k++){
                            if(row[tmp2] == str[k]){
                                cnt++;
                                if(cnt == str_len){
                                    return 1; //WE WON
                                }
                                tmp2++;
                                continue;
                            } else {
                                break;
                            }
                        }
                    }
                }
            }
            i++;
        }
        return 0; //WE DIDN'T WIN
    }
    //CONTAINS
    if(flags->contains == true){
        return 0;
    }
    return 0;
}

/// remove characters in string (currently unused) ///
void remchar(char *string, char chr){
    int j = 0;
    for (int i = 0; string[i] != '\0'; i++){ /* 'i' moves through all of original 'string' */
        if (string[i] != chr){
            string[j++] = string[i]; /* 'j' only moves after we write a non-'chr' */
        }
    }
   string[j] = '\0'; /* re-null-terminate */
}

/// remove duplicates in string ///
char *remdup(char string[], int n){
    int i,j,index = 0;
    for (i = 0; i < n; i++){ // traverse through all characters
        for (j = 0; j < i; j++){ // check if string[i] already exists (has been saved earlier)
            if (string[i] == string[j]){
                break;
            }
        }
        if (j == i){ // if it doesn't yet exist, add it to resulting string
            string[index++] = string[i];
        }
    }
    return string;
}


/**
 * [COMMANDS] FUNCTIONS
**/
/** irow R - vlozi radek tabulky pred radek R > 0 (insert-row). **/
void irow(char* delim, int cols){
    for(int i = 0; i < cols-1; i++){
        printf("%c",delim[0]);
    }
    printf("\n");
}
/** arow - prida novy radek tabulky na konec tabulky (append-row). **/
void arow(){
    ;
}
/** drow R - odstrani radek cislo R > 0 (delete-row). **/
void drow(char* row){
    int i = 0;
    while(i != '\0'){
        row[i] = ' ';
    }
    row[i-1] = '\n';
    row[i] = '\0';
}
/** 
 * @function drows N M - odstrani radky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N. 
**/
void drows(char* row){
    drow(row);
}
/** acol - prida prazdny sloupec za posledni sloupec. **/
//void acol(char* row, char* delim, flags_t* flags){
void acol(char* row, char* delim){
    int i = 0;
    char tmp[2] = " ";
    while (row[i] != '\0'){ // end of row is [\n][\0]
        i++;
    }
    /**if (flags->acol == true){
        ;
    }**/
    strncat(row,tmp,1);
    ++i;
    row[i-2] = delim[0];
    row[i-1] = '\n';
    row[i] = '\0';
    //flags->acol = true;
}



int main(int argc, char *argv[])
{
    if (argc <= 2){
        fprintf(stderr,"Error: Insufficient number of input parameters.\n");
        return 1;
    }

    flags_t flags = {false, false, false, false, false};

    bool flag1 = false;
    bool flag2 = false;

    char delim[MAX];    // array for delimiters
    int delim_len = 0;
    delim[0] = ' ';     // set it to default ' ' --> (I'm not sure if it isn't set to be a blank space as default already, because the output was the same without this line?? But I'm leaving it in just to be sure lol.)

    char row[MAX_ROW_LENGTH];

    int start = 3;

    int cols = 0; //number of columns
    int curr_row = 0; //currently printed row

    int from, to = 0; // for rows selection

    int col = 0;  // for beginswith
    char str[10]; // and contains
    int str_len = 0;

    if (strcmp(argv[1], "-d") != 0){
        fprintf(stderr,"Error: Expecting '-d', received %s.\n", argv[1]);
        return 1;
    } else { //initialize delimiter var as a 1D array and load delimiters from input arguments
        if (strcmp(argv[2], "irow") != 0 && strcmp(argv[2], "arow") != 0 && strcmp(argv[2], "drow") != 0 && strcmp(argv[2], "drows") != 0 && strcmp(argv[2], "icol") != 0 && strcmp(argv[2], "acol") != 0 && strcmp(argv[2], "dcol") != 0 && strcmp(argv[2], "dcols") != 0 &&
        strcmp(argv[2], "cset") != 0 && strcmp(argv[2], "tolower") != 0 && strcmp(argv[2], "toupper") != 0 && strcmp(argv[2], "round") != 0 && strcmp(argv[2], "int") != 0 && strcmp(argv[2], "copy") != 0 && strcmp(argv[2], "swap") != 0 && strcmp(argv[2], "move") != 0){
            strcpy(delim, argv[2]);
            delim_len = sizeof(delim)/sizeof(delim[0]); // create a variable to save the size of the delimiters string into and calculate it
            remdup(delim, delim_len);                       // then remove any duplicate characters
            //strncpy(&delim_first[0], &delim[0], 1);
        } else {
            fprintf(stderr,"It would appear the argument in place of the delimiter looks an awful lot like a command, setting it to default (space) instead. \nDid you perhaps forget to enter a delimiter? \n");
            --start;
        }
    }

/// CHECK FOR A COMMAND FOR ROWS SELECTION
    check_rowselect(start, argv, &flags, &to, &from, &col, str, &str_len); // TRY TO MERGE THE COL AND STR VARIABLES IN HERE IN THE FUTURE!!!

    //printf("just checking, start = %d?\n", start);
    while (fgets(row, MAX_ROW_LENGTH, stdin) != NULL){
        if (flag1 == true){
            flag1 = false;
        }
        curr_row++;
        for (int i = start; i < argc; i++){
            cols = calc_cols(row,delim);
            if(flags.rowsel == true){
                if (!rowsel(row, curr_row, from, to, &flags, col, str, delim, str_len)){
                    break;
                }
            }
            //printf("number of cols (before function call) is: %d\n",cols);
            if (strcmp(argv[i], "irow") == 0){
                char *ptr;
                long ret;
                ret = strtol(argv[i+1], &ptr, 10);
                if (*ptr != '\0'){
                    if (flags.argcheck == false){
                        fprintf(stderr,"Error: Passed argument 'R' of 'irow' isn't a number. \nThe program will exit, and process no further commands.\n");
                        flags.argcheck = true;
                    }
                    break;
                }
                if (ret <= 0){
                    if (flags.argcheck == false){
                        fprintf(stderr,"Error: Argument 'R' of 'irow' mustn't be a number <= 0 \nThe program will exit, and process no further commands.\n");
                        flags.argcheck = true;
                    }
                    break;
                }
                if (ret == curr_row){
                    irow(delim,cols);
                }
                ++i;
            } else if (strcmp(argv[i], "arow") == 0){
                ;
            } else if (strcmp(argv[i], "drow") == 0){
                char *ptr;
                long ret;
                ret = strtol(argv[i+1], &ptr, 10);
                if (*ptr != '\0'){
                    if (flags.argcheck == false){
                        fprintf(stderr,"Error: Passed argument 'R' of 'drow' isn't a number. \nThe program will exit, and process no further commands.\n");
                        flags.argcheck = true;
                    }
                    break;
                }
                if (ret <= 0){
                    if (flags.argcheck == false){
                        fprintf(stderr,"Error: Argument 'R' of 'drow' mustn't be a number <= 0 \nThe program will exit, and process no further commands.\n");
                        flags.argcheck = true;
                    }
                    break;
                }
                if (ret == curr_row){
                    drow(row);
                }
                ++i;
            } else if (strcmp(argv[i], "drows") == 0){
                char *ptr1, *ptr2;
                long ret1, ret2;
                ret1 = strtol(argv[i+1], &ptr1, 10);
                ret2 = strtol(argv[i+2], &ptr2, 10);
                if (*ptr1 != '\0' || *ptr2 != '\0'){
                    if (flags.argcheck == false){
                        fprintf(stderr,"Error: One or both passed arguments 'N' and 'M' of 'drows' isn't a number. \nThe program will exit, and process no further commands.\n");
                        flags.argcheck = true;
                    }
                    break;
                }
                if (ret1 <= 0 || ret2 <= 0){
                    if (flags.argcheck == false){
                        fprintf(stderr,"Error: Arguments 'N' and 'M' of 'drows' mustn't be numbers <= 0 \nThe program will exit, and process no further commands.\n");
                        flags.argcheck = true;
                    }
                    break;
                }
                if (ret1 > ret2){
                    if (flags.argcheck == false){
                        fprintf(stderr,"Error: For 'drows': Argument 'N' mustn't be > than argument 'M' \nThe program will exit, and process no further commands.\n");
                        flags.argcheck = true;
                    }
                    break;
                }
                if ((ret1 == curr_row) || (ret2 == curr_row) || (ret1 <= curr_row && ret2 >= curr_row)){
                    drows(row);
                }
                ++i;
            } else if (strcmp(argv[i], "icol") == 0){
                printf("icol reached.\n");
                ++i;
            } else if (strcmp(argv[i], "acol") == 0){
                //acol(row,delim,&flags);
                acol(row,delim);
            } else if (strcmp(argv[i], "dcol") == 0){
                printf("dcol reached.\n");
                ++i;
            } else if (strcmp(argv[i], "dcols") == 0){
                printf("dcols reached.\n");
                ++i;
                ++i;
            } else if (flag1 == false){
                if (strcmp(argv[i], "cset") == 0){
                    printf("cset reached.\n");
                    flag1 = true;
                } else if (strcmp(argv[i], "tolower") == 0){
                    printf("tolower reached.\n");
                    flag1 = true;
                } else if (strcmp(argv[i], "toupper") == 0){
                    printf("toupper reached.\n");
                    flag1 = true;
                } else if (strcmp(argv[i], "round") == 0){
                    printf("round reached.\n");
                    flag1 = true;
                } else if (strcmp(argv[i], "int") == 0){
                    printf("int reached.\n");
                    flag1 = true;
                } else if (strcmp(argv[i], "copy") == 0){
                    printf("copy reached.\n");
                    flag1 = true;
                } else if (strcmp(argv[i], "swap") == 0){
                    printf("swap reached.\n");
                    flag1 = true;
                } else if (strcmp(argv[i], "move") == 0){
                    printf("move reached.\n");
                    flag1 = true;
                }
            } else if (flag2 == false){
                flag2 = true;
                fprintf (stderr,"No commands, or two commands for data processing simultaneously, entered. \nThe program will either do nothing or ignore the second data processing command. \n");
            }
        }
        // CHECK FOR beginswith_flag AND contains_flag !!!!!!!!!!!!
        // AND SOMEHOW IMPLEMENT STARTING AND ENDING ROW !!!!!!!!!!
        print_stdin(row);
        //flags.arow = false;
    }





/********************** 
*** CHECKING OUTPUT **/
    printf ("\nargc is %i \n",argc);
    printf ("argv[2] is %s \n",argv[2]);            //! REMEMBER TO
    printf ("delim is %s \n",delim);                //! DELETE THESE
    printf ("first delimiter, at delim[0], is %c \n",delim[0]);          //! LATER ON
    printf ("delim[1] is %c \n",delim[1]);          //! YOU MONKEY
    //printf ("first delimiter is %s \n",delim_first);

    //printf("commands are: %s\n",comms);
    if (flags.rows == true){
        printf("work only from row [%d] to row [%d]\n",from,to);
    }
    if (flags.beginswith == true){
        printf("process only rows whose columns at number [%d] begin with string [%s]\n",col,str);
    }
    if (flags.contains == true){
        printf("process only rows whose columns at number [%d] contain string [%s]\n",col,str);
    }
/** CHECKING OUTPUT ***
**********************/

    printf("\nHooray! I reached the end!\n");
    return 0;
}