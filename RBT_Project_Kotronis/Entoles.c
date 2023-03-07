#include "Entoles.h"

/*
 * Typwnei to menu sto cmd tou xrhsth
 */
void PrintMenu(){
    printf("Pata : q gia quit\n");
    printf("       p gia print\n");
    printf("       i gia insert\n");
    printf("       f gia find\n");
    printf("       d gia delete\n");
    printf("       c gia clear tou dentrou\n");
    printf("       e gia elegxo\n");
    printf("       h gia print twn entolwn\n");
}

/*
 * Dexetai ws orisma dyo RedBlackTrees, ena pou exei apothikeusei akaireous kai ena me strings
 * Zhtaei apo to xrhsth na eisagei enan xarakthra wste na epilejei poio apo ta dyo dentra tha
 * tha typwthei sthn othonh
 */
void Print(const RedBlackTree rbt_int, const RedBlackTree rbt_string){
    char choice = 'a';

    printf("\nPata i gia akeraio, s gia string : ");
    fflush(stdin);
    choice = getchar();

    if(choice == 'i')
        RBT_print2D(rbt_int, INT_Print);
    else if(choice == 's')
        RBT_print2D(rbt_string, String_Print);
    else
        printf("\nEdwses lathos xarakthra...\n");
}

/*
 * Dexetai ws orisma dyo RedBlackTrees, ena pou exei apothikeusei akaireous kai ena me strings
 * Zhtaei apo to xrhsth na eisagei enan xarakthra wste na epilejei se poio apo ta dyo dentra
 * tha ginei eisagwgh stoixeiou. Epeita janazhtaei apo to xrhsth th katallhlh morfh dedomenwn
 * wste na eisagei ena kainourgio stoixeio sto antistoixo dentro kalwntas tnn RBT_Insert(...)
 */
void Insert(RedBlackTree rbt_int, RedBlackTree rbt_string){
    char choice = 'a';

    printf("\nPata i gia akeraio, s gia string : ");
    fflush(stdin);
    choice = getchar();

    if(choice == 'i'){
        printf("\nDwse mou to key pou thes na baleis : ");
        int data;
        scanf("%d", &data);
        getchar();

        int *pointer_to_data = (int*)malloc(sizeof(int));
        *pointer_to_data = data;

        RBT_Insert(rbt_int, (void*)pointer_to_data, INT_isLessThan);
    }
    else if(choice == 's'){
        printf("\nDwse ena string mexri %d xarakthres : ", SIZE_OF_STRING-1);

        char *data = (char*)malloc(SIZE_OF_STRING*sizeof(char));
        scanf("%s", data);
        getchar();

        RBT_Insert(rbt_string, (void*)data, String_isLessThan);
    }
    else
        printf("\nEdwses lathos xarakthra...\n");
}

/*
 * Dexetai ws orisma dyo RedBlackTrees, ena pou exei apothikeusei akaireous kai ena me strings
 * Zhtaei apo to xrhsth na eisagei enan xarakthra wste na epilejei se poio apo ta dyo dentra
 * tha ginei h anazhthsh tou stoixeiou. Epeita janazhtaei apo to xrhsth to stoixeio pou thelei na
 * na anazhthsei kai typwnei mhynmha gia to an brethike h oxi to stoixeio
 */
void Find(const RedBlackTree rbt_int, const RedBlackTree rbt_string){
    char choice = 'a';

    printf("\nPata i gia akeraio, s gia string : ");
    fflush(stdin);
    choice = getchar();

    if(choice == 'i'){
        printf("\nDwse to key pou thes na breis :");
        int keytofind;
        scanf("%d", &keytofind);
        getchar();

        if(RBT_Search(rbt_int, &keytofind, INT_isLessThan, INT_isEqual))
            printf("\nBrethike to kleidi %d\n", keytofind);
        else
            printf("\nTo kleidi %d den yparxei\n", keytofind);
    }
    else if(choice == 's'){
        printf("\nDwse ena string mexri %d xarakthres : ", SIZE_OF_STRING-1);

        char data[SIZE_OF_STRING];
        scanf("%s", data);
        getchar();

        if(RBT_Search(rbt_string, data, String_isLessThan, String_isEqual))
            printf("\nBrethike to kleidi %s\n", data);
        else
            printf("\nTo kleidi %s den yparxei\n", data);
    }
    else
        printf("\nEdwses lathos xarakthra...\n");
}

/*
 * Dexetai ws orisma dyo RedBlackTrees, ena pou exei apothikeusei akaireous kai ena me strings
 * Zhtaei apo to xrhsth na eisagei enan xarakthra wste na epilejei se poio apo ta dyo dentra
 * tha ginei diagrafei stoixeiou. Epeita janazhtaei apo to xrhsth to stoixeio pou thelei na
 * na diagrajei kai typwnei mhynmha gia to an egine h diagrafh tou stoixeiou h oxi
 */
void Delete(RedBlackTree rbt_int, RedBlackTree rbt_string){
    char choice = 'a';

    printf("\nPata i gia akeraio, s gia string : ");
    fflush(stdin);
    choice = getchar();

    if(choice == 'i'){
        printf("\nDwse to key pou thes na diagrajeis :");
        int key_to_delete;
        scanf("%d", &key_to_delete);
        getchar();

        int node_deleted = RBT_Delete(rbt_int, &key_to_delete, INT_isLessThan, INT_isEqual);
        if(!node_deleted)
            printf("\nTo kleidi %d den yparxei\n", key_to_delete);
    }
    else if(choice == 's'){
        printf("\nDwse to string pou thes na diagrajeis : ");

        char string_to_delete[SIZE_OF_STRING];
        scanf("%s", string_to_delete);
        getchar();

        int node_deleted = RBT_Delete(rbt_string, &string_to_delete, String_isLessThan, String_isEqual);
        if(!node_deleted)
            printf("\nTo kleidi %s den yparxei\n", string_to_delete);
    }
    else
        printf("\nEdwses lathos xarakthra...\n");
}

/*
 * Dexetai ws orisma dyo RedBlackTrees, ena pou exei apothikeusei akaireous kai ena me strings
 * Zhtaei apo to xrhsth na eisagei enan xarakthra wste na epilejei poio apo ta dyo dentra  tha
 * diagrafei. Epeita typwnei mhynmha gia to an egine h diagrafh h oxi
 */
void Clear(RedBlackTree rbt_int, RedBlackTree rbt_string){
    char choice = 'a';

    printf("\nPata i gia akeraio, s gia string : ");
    fflush(stdin);
    choice = getchar();

    if(choice == 'i'){
        int deleted = RBT_Free(rbt_int);

        if(deleted)
            printf("\nTo dentro diagrafhke\n");
        else
            printf("\nTo dentro de mporese na diagrafei kathos exei stoixeia mesa\n");
    }
    else if(choice == 's'){
        int deleted = RBT_Free(rbt_string);

        if(deleted)
            printf("\nTo dentro diagrafhke\n");
        else
            printf("\nTo dentro de mporese na diagrafei kathos exei stoixeia mesa\n");
    }
    else{
        printf("\nEdwses lathos xarakthra...\n");
    }
}

/*
 * Dexetai ws orisma dyo RedBlackTrees, ena pou exei apothikeusei akaireous kai ena me strings
 * Zhtaei apo to xrhsth na eisagei enan xarakthra wste na epilejei se poio apo ta dyo dentra
 * tha ginei elegxos an einai adeio
 *
 * !!!Prosoxh autos o elegxos tha prepei na ginei mono otan to dentro den einai NULL alliws
 * yparxei kindynos gia SEG FAULT
 */
void isEmpty(const RedBlackTree rbt_int, const RedBlackTree rbt_string){
    char choice = 'a';

    printf("\nPata i gia akeraio, s gia string : ");
    fflush(stdin);
    choice = getchar();

    if(choice == 'i'){
        if(RBT_isEmpty(rbt_int))
                printf("\nTo dentro einai keno");
    }
    else if(choice == 's'){
        if(RBT_isEmpty(rbt_string))
                printf("\nTo dentro einai keno");
    }
    else{
        printf("\nEdwses lathos xarakthra...\n");
    }
}
