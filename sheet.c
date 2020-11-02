#include <stdio.h>
#include <stdlib.h>

/** TODO: 

Uprava velikosti tabulky:
./sheet [-d DELIM] [Prikazy pro upravu tabulky]
nebo zpracovani dat:
./sheet [-d DELIM] [Selekce radku] [Prikaz pro zpracovani dat]

--> Argument -d specifikuje, jake znaky lze interpretovat jako oddelovace jednotlivych bunek. Kazdy znak ve vstupnim radku, ktery je obsazen v retezci DELIM, 
se chova jako oddelovac dvou sousedicich bunek. Ve vychozim nastaveni je DELIM retezec obsahujici mezeru. Vicenasobny vyskyt stejnych znaku v retezci DELIM je 
ignorovan. Prvni znak z retezce DELIM bude take pouzit jako oddelovac vystupnich hodnot.

*******************
*  Uprava tabulky
*******************
-Prikazu pro upravu tabulky muze byt zadano vice. V takovem pripade budou zadany jako sekvence vice argumentu prikazove radky:

Prikazy pro upravu tabulky:

irow R - vlozi radek tabulky pred radek R > 0 (insert-row).
arow - prida novy radek tabulky na konec tabulky (append-row).
drow R - odstrani radek cislo R > 0 (delete-row).
drows N M - odstrani radky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N.
icol C - vlozi prazdny sloupec pred sloupec dany cislem C.
acol - prida prazdny sloupec za posledni sloupec.
dcol C - odstrani sloupec cislo C.
dcols N M - odstrani sloupce N az M (N <= M). V pripade N=M se prikaz chova stejne jako dcol N.

*******************
*  Zpracovani dat
*******************
-Zpracovanu dat predstavuje upravy obsahu jednotlivych bunek tabulky. Kazde spusteni programu muze obsahovat nejvice jeden prikaz pro zpracovani dat. 

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
cseq N M B - do buněk ve sloupcích N až M včetně vloží postupně rostoucí čísla (o jedničku) počínaje hodnotou B.
rseq C N M B - ve sloupci C do buněk každého řádku od řádku N po řádek M včetně vloží rostoucí čísla počínaje hodnotou B. Číslo M může být nahrazeno pomlčkou. V takovém případě se tím myslí poslední řádek souboru.
rsum C N M - do buňky ve sloupci C na řádku M+1 vloží součet hodnot buněk ve sloupci C na řádcích N až M včetně.
ravg C N M - obdobně jako rsum, avšak výsledná hodnota představuje aritmetický průměr.
rmin C N M - obdobně jako rsum, avšak výsledná hodnota představuje nejmenší hodnotu.
rmax C N M - obdobně jako rsum, avšak výsledná hodnota představuje největší hodnotu.
rcount C N M - obdobně jako rsum, avšak výsledná hodnota představuje počet neprázdnných hodnot daných buněk.

**/

int main(int argc, char *argv[])
{
    printf("Neco tu jako musi prozatim byt no...\n");
    return 0;
}