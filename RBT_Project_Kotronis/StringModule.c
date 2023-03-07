#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringModule.h"

/*
 * Dexetai ws orisma ena const void pointer pou theixnei se string  kai epeita typwnei
 * th sygkekrimenh symboloseira sthn othonh
 */
void String_Print(const void* item){
    printf("%s", (char*)item);
}

/*
 * Dexetai ws orismata dyo const void pointer pou theixnoun se string kai ektelei
 * lexicographically conmaprison anamesa sta dyo string kai epistrefei 0 ean to
 * prwto string einai mikrotero lexicographically apo to deutero eidalos epistrefei 1
 */
int String_isLessThan(const void *item1, const void *item2){
    char *temp = (char*)item1;
    char *aux  = (char*)item2;

    int Result = strcmp(temp, aux);

    if(Result < 0)
        return 1;
    else
        return 0;
}

/*
 * Dexetai ws orismata dyo const void pointer pou theixnoun se string kai ektelei
 * lexicographically conmaprison anamesa sta dyo string kai epistrefei 0 ean to
 * prwto string einai iso lexicographically me to deutero eidalos epistrefei 1
 */
int String_isEqual(const void *item1, const void *item2){
    char *temp = (char*)item1;
    char *aux  = (char*)item2;

    int Result = strcmp(temp, aux);

    if(Result == 0)
        return 1;
    else
        return 0;
}
