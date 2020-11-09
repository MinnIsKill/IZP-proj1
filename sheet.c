#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100
#define MAX_ROW_LENGTH 10242

/** TODO:.

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
GitHub commit flow: $ git add .
                    $ git commit -m "message"
                    $ git push --set-upstream origin main   (where 'main' is name of branch to commit to)
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

void random_func(char *row){
    printf("%s", row);
}

/// remove characters in string (currently unused) ///
void remchar(char *string, char chr){
    int i, j = 0;
    for (i = 0; string[i] != '\0'; i++){ /* 'i' moves through all of original 'string' */
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





int main(int argc, char *argv[])
{
    if (argc <= 2){
        printf("Insufficient amount of input parameters.\n");
        return 1;
    }

    //bool flag1 = false;
    bool flag2 = false;

    char delim[MAX];    // array for delimiters
    //char delim_first;   // first char of delim string, supposed to be used as a separator in final file
    delim[0] = ' ';     // set it to default ' ' --> (I'm not sure if it isn't set to be a blank space as default already, because the output was the same without this line?? But I'm leaving it in just to be sure lol.)

    char row[MAX_ROW_LENGTH];
    char comms[100];

    int to, from = 0; // for rows selection
    while (fgets(row, MAX_ROW_LENGTH, stdin) != NULL){
        to++;}

    bool beginswith_flag = false;
    int beginswith_col;
    char beginswith_str[10];

    bool contains_flag = false;
    int contains_col;
    char contains_str[10];

    if (strcmp(argv[1], "-d") != 0){
        printf("Error: Expecting '-d', received %s.\n", argv[1]);
        return 1;
    } else { //initialize delimiter var as a 1D array and load delimiters from input arguments
        if (strcmp(argv[2], "irow") != 0 && strcmp(argv[2], "arow") != 0 && strcmp(argv[2], "drow") != 0 && strcmp(argv[2], "drows") != 0 && strcmp(argv[2], "icol") != 0 && strcmp(argv[2], "acol") != 0 && strcmp(argv[2], "dcol") != 0 && strcmp(argv[2], "dcols") != 0){
            strcpy(delim, argv[2]);
            int delim_len = sizeof(delim)/sizeof(delim[0]); // create a variable to save the size of the delimiters string into and calculate it
            remdup(delim, delim_len);                       // then remove any duplicate characters
            //delim_first = delim[0];
            printf ("argv[2] is %s \n",argv[2]);            //! REMEMBER TO
            printf ("delim is %s \n",delim);                //! DELETE THESE
            printf ("delim[0] is %c \n",delim[0]);          //! LATER ON
            printf ("delim[1] is %c \n",delim[1]);          //! YOU MONKEY
        }
    }
  
    for (int i = 3; i < argc; i++) //THIS STILL DOESN'T COUNT WITH NO DELIM INITIALIZATION, DON'T FORGET TO LOOK AT IT LATER (might have to change it to a while loop)
    {
        if (strcmp(argv[i], "rows") == 0){
            from = atoi(argv[i+1]);
            to = atoi(argv[i+2]);
        } else if (strcmp(argv[i], "beginswith") == 0){
            beginswith_flag = true;
            beginswith_col = atoi(argv[i+1]);
            strcpy(beginswith_str, argv[i+2]);
        } else if (strcmp(argv[i], "contains") == 0){
            contains_flag = true;
            contains_col = atoi(argv[i+1]);
            strcpy(contains_str, argv[i+2]);
        } else if (strcmp(argv[i], "irow") == 0){
            strncat(comms, "irow\n", 6);
            strncat(comms, argv[i+1], 5);
            strncat(comms, "\n", 2);
        } else if (strcmp(argv[i], "arow") == 0){
            strncat(comms, "arow\n", 6);
        } else if (strcmp(argv[i], "drow") == 0){
            strncat(comms, "drow\n", 6);
            strncat(comms, argv[i+1], 5);
            strncat(comms, "\n", 2);
        } else if (strcmp(argv[i], "drows") == 0){
            strncat(comms, "drows\n", 7);
            strncat(comms, argv[i+1], 5);
            strncat(comms, "\n", 2);
            strncat(comms, argv[i+2], 5);
            strncat(comms, "\n", 2);
        } else if (strcmp(argv[i], "icol") == 0){
            printf("icol reached.\n");
        } else if (strcmp(argv[i], "acol") == 0){
            printf("acol reached.\n");
        } else if (strcmp(argv[i], "dcol") == 0){
            printf("dcol reached.\n");
        } else if (strcmp(argv[i], "dcols") == 0){
            printf("dcols reached.\n");
        } else if (flag2 == false){
            if (strcmp(argv[i], "cset") == 0){
                printf("cset reached.\n");
                flag2 = true;
            } else if (strcmp(argv[i], "tolower") == 0){
                printf("tolower reached.\n");
                flag2 = true;
            } else if (strcmp(argv[i], "toupper") == 0){
                printf("toupper reached.\n");
                flag2 = true;
            } else if (strcmp(argv[i], "round") == 0){
                printf("round reached.\n");
                flag2 = true;
            } else if (strcmp(argv[i], "int") == 0){
                printf("int reached.\n");
                flag2 = true;
            } else if (strcmp(argv[i], "copy") == 0){
                printf("copy reached.\n");
                flag2 = true;
            } else if (strcmp(argv[i], "swap") == 0){
                printf("swap reached.\n");
                flag2 = true;
            } else if (strcmp(argv[i], "move") == 0){
                printf("move reached.\n");
                flag2 = true;
            }
        } else {
            printf ("no args\n");
        }
    }


    while (fgets(row, MAX_ROW_LENGTH, stdin) != NULL){
        // CHECK FOR beginswith_flag AND contains_flag !!!!!!!!!!!!
        // AND SOMEHOW IMPLEMENT STARTING AND ENDING ROW !!!!!!!!!!
        random_func(row);
    }

/********************** 
*** CHECKING OUTPUT **/
    printf("commands are: %s\n",comms);
    printf("from row %d\n",from);
    printf("to row %d\n",to);
    if (beginswith_flag == true){
        printf("process only rows whose cols at number: %d\n",beginswith_col);
        printf("begin with string: %s\n",beginswith_str);
    }
    if (contains_flag == true){
        printf("process only rows whose cols at number: %d\n",contains_col);
        printf("contain string: %s\n",contains_str);
    }
/** CHECKING OUTPUT ***
**********************/

    printf("Hooray! I reached the end!\n");
    return 0;
}