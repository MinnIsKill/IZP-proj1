#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("argc je %d\n", argc);
    int i = 0;
    while (i < argc){
        printf("argv[%d] je %s\n", i, argv[i]);
        i++;
    }

/** atoi dostane retezec a vrati cislo, atof dostane retezec a vrati float
    musim si jako druhy argument zavolat cislo a jako ctvrty desetinne cislo.  **/

    int integer = atoi(argv[2]);
    printf("integer je %d\n", integer);
    float real = atof(argv[4]);
    printf("real je %f\n", real);

    int j = atoi("aa");
    printf("j je %d",j);

    return 0;
}