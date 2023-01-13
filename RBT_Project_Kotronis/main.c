#include <stdio.h>
#include <stdlib.h>
#include "RBT.h"

tp root, Tnill;

int main()
{
    char c = 'a';

    Tnill = (tp)malloc(sizeof(struct Node));
    Tnill -> r = NULL;
    Tnill -> l = NULL;
    Tnill -> p = NULL;
    Tnill -> key = 0;
    Tnill -> color = 'B';

    root = Tnill;

    while(c != 'q'){
        printf("\nPata q gia quit, p gia print, i gia insert, f gia find, d gia delete : ");
        fflush(stdin);
        c = getchar();

        if(c == 'q'){
            printf("\n~~~~~QUITING~~~~~");
        }
        if(c == 'p'){
            RBT_print2D(root);
        }
        if(c == 'i'){
            printf("\nDwse mou to key pou thes na baleis : ");
            int data;
            scanf("%d", &data);
            getchar();

            RBT_Insert(&root, data);                //me loops
        }
        if(c == 'f'){
            printf("\nDwse to key pou thes na breis :");
            int keytofind;
            scanf("%d", &keytofind);
            getchar();

            RBT_Search(root, keytofind);              //me loops
        }
        if(c == 'd'){
            printf("\nDwse to key pou thes na diagrajeis :");
            int keytofind;
            scanf("%d", &keytofind);
            getchar();

            RBT_Delete(&root, &root, keytofind);

            Tnill -> p = NULL;

        }// ta parakatw einai gia debug kai einai kryfa
        if(c == 't'){
            RBT_Insert(&root, 10);
            RBT_Insert(&root, 18);
            RBT_Insert(&root, 7);
            RBT_Insert(&root, 15);
            RBT_Insert(&root, 16);
            RBT_Insert(&root, 30);
            RBT_Insert(&root, 25);
            RBT_Insert(&root, 40);

        }
        if(c == 'T'){
            for(int i = 1; i < 100; i++)
                RBT_Insert(&root, i);

            for(int i = 30; i < 36; i++){
                RBT_Delete(&root, &root, i);
                Tnill -> p = NULL;
            }
        }
        if(c == 'k'){
            if(root -> l == Tnill)
                printf("\nL tsek");
            if(root -> r == Tnill)
                printf("\nR tsek");
            if(root -> p == Tnill)
                printf("\nP tsek");
            if(root -> p -> p != NULL)
                printf("\nThema me to Tnill");
        }
        if(c == 'v'){
            Violation_Of_Rule_Number_3(root);
            Violation_Of_Rule_Number_4(root);
        }
        if(c == 'w'){
                printf("\nTo key tou root einai : %d", root -> key);

                if(root -> p == Tnill){
                    printf("\nTo p tou root einai to Tnill");
                }
        }
    }
    return 0;
}
