#include "Entoles.h"

int main()
{
    char choice = 'a';

    RedBlackTree RBT_of_int = RBT_New();
    RedBlackTree RBT_of_string = RBT_New();

    PrintMenu();
    while(1){
        printf("\nDwse mia entolh : ");
        fflush(stdin);
        choice = getchar();

        if(choice == 'q'){
            break;
        }
        if(choice == 'p'){
            Print(RBT_of_int, RBT_of_string);
        }
        if(choice == 'i'){
            Insert(RBT_of_int, RBT_of_string);
        }
        if(choice == 'f'){
            Find(RBT_of_int, RBT_of_string);
        }
        if(choice == 'd'){
            Delete(RBT_of_int, RBT_of_string);
        }
        if(choice == 'c'){
            Clear(RBT_of_int, RBT_of_string);
        }
        if(choice == 'e'){
            isEmpty(RBT_of_int, RBT_of_string);
        }
        if(choice == 'h'){
            PrintMenu();
        }
    }

    printf("\n~~~~~QUITING~~~~~");

    return 0;
}



