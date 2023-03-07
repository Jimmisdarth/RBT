#include <stdio.h>
#include <stdlib.h>
#include "IntModule.h"

/*
 * Dexetai ws orisma ena const void pointer pou theixnei se akeraio kai epeita typwnei
 * th sygkekrimenh akeraio sthn othonh
 */
void INT_Print(const void* item){
    printf("%d", *(int*)item);
}

/*
 * Dexetai ws orismata dyo const void pointer pou theixnoun se akeraious. Ean o item1 einai
 * mikroteros apo ton item2 tote epistrefei 1 eidalws epistrfei 0
 */
int INT_isLessThan(const void *item1, const void *item2){
    int *temp = (int*)item1;
    int *aux  = (int*)item2;

    if(*temp < *aux)
        return 1;
    else
        return 0;
}

/*
 * Dexetai ws orismata dyo const void pointer pou theixnoun se akeraious. Ean o item1 einai
 * iso me ton item2 tote epistrefei 1 eidalws epistrfei 0
 */
int INT_isEqual(const void *item1, const void *item2){
    int *temp = (int*)item1;
    int *aux  = (int*)item2;

    if(*temp == *aux)
        return 1;
    else
        return 0;
}
