#include "RBT.h"
#include <stdio.h>
#include <stdlib.h>

#define COUNT 20

/*O Tnill kombos pou xreiazetai gia na anaparisoume ta fylla*/
struct Node nill = { .key = 0, .color = 'B', .r = NULL, .l = NULL, .p = NULL };
tp Tnill = &nill;

void print2DUtil(tp root, int space);

void LeftRotate(tp *x);
void RightRotate(tp *x);

void findnode(tp root, int data);

void RBInsertFixUp(tp *z, tp *root);

void RBDeleteFixUp(tp *Troot, tp x);

void Violation_Of_Rule_Number_3(tp root);
void Violation_Of_Rule_Number_4(tp root);


/*
//  Print Functions
*/

void print2DUtil(tp root, int space)
{
    // Base case
    if (root == Tnill)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->r, space);

    // Print current node after space
    // count
    printf("\n");
    int i;
    for (i = COUNT; i < space; i++)
        printf(" ");
    printf("%d %c\n", root->key, root -> color);

    // Process left child
    print2DUtil(root->l, space);
}

// Wrapper over print2DUtil()
void RBT_print2D(tp root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

/*
//  Find Functions
*/

void findnode(tp root, int data){
    if(root -> key == data){
        printf("\nBrethike to kleidi %d", root -> key);
    }
    if(root -> key > data && root -> l != NULL){
        findnode(root -> l, data);
    }
    if(root -> key < data && root -> r != NULL){
        findnode(root -> r, data);
    }
}

void RBT_Search(tp root, int data){
    while(root != Tnill && root -> key != data){
       if(root -> key > data){
        root = root -> l;
       }
       else{
        root = root -> r;
       }
    }

    if(root != Tnill)
        printf("\nBrethike to kleidi %d l -> key %d, r -> key %d", root -> key, root -> l -> key, root -> r -> key);
    else
        printf("\nTo kleidi %d den yparxei", data);
}

/*
//  Rotation Functions
*/

void LeftRotate(tp *x){
    if((*x) -> r != Tnill){
        tp temp, aux;
        aux = (*x);
        temp = aux -> r;

        aux -> r = temp -> l;
        if(temp -> l != Tnill){
            aux -> r -> p = aux;
        }

        temp -> p = aux -> p;
        if(aux -> p != Tnill && aux == aux -> p -> l){ // to aux einai aristero paidi
            aux -> p -> l = temp;
        }
        if(aux -> p != Tnill && aux == aux -> p -> r){ //to aux einai deji paidi
            aux -> p -> r = temp;
        }

        temp -> l = aux;
        aux -> p = temp;

        (*x) = temp;

    }
}

void RightRotate(tp *x){
    if((*x) -> l != Tnill){
        tp temp, aux;
        aux = (*x);
        temp = aux -> l;

        aux -> l = temp -> r;
        if(temp -> r != Tnill){
            aux -> l -> p = aux;
        }

        temp -> p = aux -> p;

        if(aux -> p != Tnill && aux == aux -> p -> l){ // to aux einai aristero paidi
            aux -> p -> l = temp;
        }
        if(aux -> p != Tnill && aux == aux -> p -> r){ //to aux einai deji paidi
            aux -> p -> r = temp;
        }

        temp -> r = aux;
        aux -> p = temp;

        (*x) = temp;
    }
}

/*
//  Insert Functions
*/

void RBInsertFixUp(tp *z, tp *root){


    while((*z) -> p != Tnill && (*z) -> p -> color == 'R'){
            if((*z) -> p -> color == 'R'){                                                   //ean o mpampas tou node einai kokkinos tote : (4)
                if(((*z) -> p -> p -> r) == ((*z) -> p)){           //elegxei an o mpampas einai deji paidi
                    if(((*z) -> p -> p -> l -> color) == 'R'){  //elegxei an o theios einai kokkinos kai oxi null (b)
                        (*z) -> p -> color = 'B';
                        (*z) -> p -> p -> l -> color = 'B';                                      //tote kanoume recoloring tou mpampa kai tou theiou

                        if((*z) -> p -> p -> p != Tnill){                                         //elegxoume an o papous einai to root
                            (*z) -> p -> p -> color = 'R';
                            (*z) = (*z) -> p -> p;                                       //an den einai to janaxromatizoume
                            //RBInsertFixUp(&(*z) -> p -> p, &(*root));
                        }
                    }
                    else{
                        if((*z) -> p -> p -> l -> color == 'B'){ //elegxei an o theios einai null h mauros (a)
                            if((*z) == (*z) -> p -> l){                                           //elegxei an to node einai aristero paidi
                                (*z) = (*z) -> p;                                                 //an einai kanei prwta right rotate

                                //RightRotate2(&(*z), 0);
                                RightRotate(&(*z));


                                //kwdiko gia rightrotate

                                (*z) -> color = 'B';
                                (*z) -> p -> color = 'R';

                                //LeftRotate(&(*z) -> p -> p))
                                //kwdikos gia leftrotate tou papou gt me synarthsh den

                                (*z) = (*z) -> p;

                                //LeftRotate(&(*z));

                                tp right = (*z)->r;
                                (*z)->r = right->l;
                                if ((*z)->r)
                                    (*z)->r->p = (*z);
                                right->p = (*z)->p;
                                if (!((*z)->p))
                                    (*root) = right;
                                else if ((*z) == (*z)->p->l)
                                    (*z)->p->l = right;
                                else
                                    (*z)->p->r = right;
                                right->l = (*z);
                                (*z)->p = right;
                            }
                            else{                                       //to node einai deji paidi
                                (*z) -> p -> color = 'B';
                                (*z) -> p -> p -> color = 'R';

                                //LeftRotate(&(*z) -> p -> p))
                                //kwdikow gia Leftrotate

                                (*z) = (*z) -> p -> p;

                                tp right;
                                right = (*z) -> r;
                                (*z)->r = right->l;

                                if ((*z)->r != Tnill)
                                    (*z)->r->p = (*z);
                                right->p = (*z)->p;
                                if (((*z)->p) == Tnill)
                                    (*root) = right;
                                else if ((*z) == (*z)->p->l)
                                    (*z)->p->l = right;
                                else
                                    (*z)->p->r = right;
                                right->l = (*z);
                                (*z)->p = right;
                            }
                        }
                    }
                }
                else{
                    if((*z) -> p == (*z) -> p -> p -> l){         //elegxei an o mpampas einai aristero paidi : (4)
                        if((*z) -> p -> p -> r -> color == 'B'){  //elegxei an o theios einai null h mauros (a)
                            if((*z) == (*z) -> p -> r){                                          //elegxei an to node einai deji paidi
                                (*z) = (*z) -> p;

                                LeftRotate(&(*z));
                                //kwdikos gia leftrotate

                                (*z) -> color = 'B';
                                (*z) -> p -> color = 'R';

                                //RightRotate(&((*z) -> p -> p))
                                //kwdikos gia RR tou papou giati me synarthsh ta ekane mantara

                                (*z) = (*z) -> p;

                                tp left = (*z)->l;
                                (*z)->l = left->r;

                                if ((*z)->l)
                                    (*z)->l->p = (*z);

                                left->p = (*z)->p;

                                if (!((*z)->p))
                                    (*root) = left;
                                else if ((*z) == (*z)->p->l)
                                    (*z)->p->l = left;
                                else
                                    (*z)->p->r = left;
                                left->r = (*z);
                                (*z)->p = left;
                            }
                            else{                                                                   //an einai aristero paidi
                                (*z) -> p -> color = 'B';
                                (*z) -> p -> p -> color = 'R';

                                //RightRotate2(&((*z) -> p -> p), 1);
                                (*z) = (*z) -> p -> p;                     //mporei kai kodikos gia RR

                                tp left = (*z)->l;
                                (*z)->l = left->r;
                                if ((*z)->l != Tnill)
                                    (*z)->l->p = (*z);
                                left->p = (*z)->p;
                                if (((*z)->p) == Tnill)
                                    (*root) = left;
                                else if ((*z) == (*z)->p->l)
                                    (*z)->p->l = left;
                                else
                                    (*z)->p->r = left;
                                left->r = (*z);
                                (*z)->p = left;
                            }

                        }
                        else{
                            if(((*z) -> p -> p -> r -> color) == 'R'){  //elegxei an o theios einai kokkinos kai oxi null (b)
                                (*z) -> p -> color = 'B';
                                (*z) -> p -> p -> r -> color = 'B';                                      //tote kanoume recoloring tou mpampa kai tou theiou

                                if((*z) -> p -> p -> p != Tnill){                                         //elegxoume an o papous einai to root
                                    (*z) -> p -> p -> color = 'R';
                                    (*z) = (*z) -> p -> p;                                               //an den einai to janaxromatizoume
                                    //RBInsertFixUp(&(*z) -> p -> p, &(*root));
                                }
                            }
                        }
                    }

                }
            }
    }
    if((*z) -> p == Tnill){    //an to node einai to root tote balto mauro (1)
        (*z) -> color = 'B';
    }
}

void RBT_Insert(tp *root, int data){ // isnertion me while loops
    tp y, x, temp;
    y = Tnill;
    x = (*root);

    while(x != Tnill){
        y = x;
        if(data < x -> key){
            x = x -> l;
        }
        else{
            x = x -> r;
        }
    }

    temp = (tp)malloc(sizeof(struct Node));
    temp -> l = temp -> r = Tnill;
    temp -> p = y;
    temp -> key = data;
    temp -> color = 'R';

    if(y == Tnill){//to dentro einai keno
        temp -> l = temp -> r =(*root);
        (*root) = temp;
    }
    else{
        if(data < y -> key && y -> l == Tnill){
            temp -> l = temp -> r = y -> l;
            y -> l = temp;
        }
        if(data > y -> key && y -> r == Tnill){
            temp -> l = temp -> r = y -> r;
            y -> r = temp;
        }
    }

    RBInsertFixUp(&temp, &(*root));

    //Tsekarei an exoun ginei parabiaseis otan teleiwsei me ta fixup
    //Violation_Of_Rule_Number_3(*root);
    //Violation_Of_Rule_Number_4(*root);
}

/*
//  Delete Functions
*/

void RBDeleteFixUp(tp *Troot, tp x){

    //print2D(x);

    int T = 0; //tha thesoume auto iso me to 1 otan the exoume teleiwsei me to case 4

    while(T != 1 && (x) -> color == 'B' && (x) != (*Troot)){
            if((x) == (x) -> p -> l){             //to x einai aristero paidi
                tp w = (x) -> p -> r;              //w o aderfos tou x
                if(w -> color == 'R'){              //to einai kokkino
                    (x) -> p -> r -> color = 'B';
                    (x) -> p -> color = 'R';
                    if(x -> p == (*Troot)){
                        LeftRotate(&((x) -> p));
                        (*Troot) = w;

                        (*Troot) -> l -> l -> p = (*Troot) -> l;
                        x = (*Troot) -> l -> l;

                        w = (x) -> p -> r;
                    }
                    else{
                        LeftRotate(&((x) -> p));

                        x -> p = w -> l;

                        w = (x) -> p -> r;
                    }
                }
                if((w-> l -> color == 'B') && (w-> r -> color == 'B')){    //to w exei dyo maura paidia
                    (x) -> p -> r -> color = 'R';
                    (x) = (x) -> p;
                }
                else if (w -> r -> color == 'B' && w -> l -> color == 'R'){  //to exei mauro to deji paidi kai kokkino to aristero
                    x -> p -> r -> l -> color ='B';

                    x -> p -> r -> color = 'R';

                    RightRotate(&(x -> p -> r));             //RightRotate(&(x -> p -> r));

                    w = x -> p -> r;
                }
                if(w -> color == 'B' && w -> r -> color == 'R'){            //to w einai mauro kai exei kokkino deji paidi
                    x -> p -> r -> color = x -> p -> color;
                    x -> p -> color = 'B';


                    x -> p -> r -> r -> color = 'B';

                if(x -> p == (*Troot)){
                        LeftRotate(&((x) -> p));
                        (*Troot) = w;

                        T = 1;
                    }
                    else{
                        LeftRotate(&((x) -> p));

                        T = 1;
                    }
                }
            }
            else{                                  //to x einai deji paidi
                tp w = (x) -> p -> l;              //w o aderfos tou x
                if(w -> color == 'R'){                  //to w einai kokkino
                    (x) -> p -> l -> color = 'B';
                    (x) -> p -> color = 'R';

                    if(x -> p == (*Troot)){
                        RightRotate(&((x) -> p));
                        (*Troot) = w;

                        (*Troot) -> r -> r -> p = (*Troot) -> r;
                        x = (*Troot) -> r -> r;

                        w = (x) -> p -> l;

                    }
                    else{
                        RightRotate(&((x) -> p));

                        x -> p = w -> r;

                        w = (x) -> p -> l;
                    }
                }
                if((w -> l -> color == 'B') && (w -> r -> color == 'B')){   //to w exei dyo maura paidia
                    (x) -> p -> l -> color = 'R';
                    (x) = (x) -> p;
                }
                else if (w -> l -> color == 'B' && w -> r -> color == 'R'){
                    x -> p -> l -> r -> color ='B';

                    x -> p -> l -> color = 'R';

                    LeftRotate(&(x -> p -> l));             //RightRotate(&(x -> p -> r));
                    w = x -> p -> l;
                }
                if(w -> color == 'B' && w -> l -> color == 'R'){
                x -> p -> l -> color = x -> p -> color;
                x -> p -> color = 'B';

                x -> p -> l -> l -> color = 'B';

                if(x -> p == (*Troot)){
                        RightRotate(&((x) -> p));
                        (*Troot) = w;

                        T = 1;
                    }
                    else{
                        RightRotate(&((x) -> p));

                        T = 1;
                    }
                }
            }
    }
    (x) -> color = 'B';
}

void RBT_Delete(tp *Treeroot, tp *root, int data){
    if((*root) != Tnill && ((*root) -> key) > data){
        RBT_Delete(&(*Treeroot), &(*root) -> l, data);
    }
    if((*root) != Tnill && ((*root) -> key) < data){
        RBT_Delete(&(*Treeroot), &(*root) -> r, data);
    }
    if((*root) == Tnill){
        printf("\nTo dentro einai keno...");
    }
    if((*root) != Tnill && ((*root) -> key) == data){

        tp y;
        y = (*root);

        char Ysoriginalcolor = y -> color;

        if((*root) -> l == Tnill && (*root) -> r == Tnill){ // diagrafh fyllou
            //printf("\nLEAF");
            tp temp = (*root);

            (*root) -> l -> p = (*root) -> p;
            (*root) = (*root) -> l;

            free(temp);
            (temp) = NULL;

            if(Ysoriginalcolor == 'B'){
                RBDeleteFixUp(&(*Treeroot), (*root));
            }
        }
        if((*root) != Tnill && (*root) -> l != Tnill && (*root) -> r == Tnill){ // diagrafh kombou me aristero paidi
            //printf("\nARISTERO");
            tp temp;
            temp = (*root);

            (*root) -> l -> p = (*root) -> p;
            (*root) = (*root) -> l;
            free(temp);
            temp = NULL;

            if(Ysoriginalcolor == 'B'){
                RBDeleteFixUp(&(*Treeroot), (*root));
            }
        }
        if((*root) != Tnill && ((*root) -> key) == data && (*root) -> r != Tnill && (*root) -> l == Tnill){ // diagrafh kombou me deji paidi
            //printf("\nDEJI");
            tp temp;
            temp = (*root);

            (*root) -> r -> p = (*root) -> p;
            (*root) = (*root) -> r;
            free(temp);
            temp = NULL;

            if(Ysoriginalcolor == 'B'){
                RBDeleteFixUp(&(*Treeroot), (*root));
            }
        }
        if((*root) != Tnill && ((*root) -> key) == data && (*root) -> l != Tnill && (*root) -> r != Tnill){ // diagrafh komvou me 2 paidia
            //printf("\n2PAIDIA");
            tp aux;
            aux = (*root) -> r;

            while(aux -> l != Tnill){
                aux = aux -> l;
            }
            int keytorestore;
            keytorestore = aux -> key;
            Ysoriginalcolor = aux -> color;

            if(aux -> r != Tnill){
                aux -> r -> p = aux -> p;
            }

            //printf("\nkey = %d", aux -> key);

            (*root) -> key = keytorestore;
            RBT_Delete(&(*Treeroot), &((*root) -> r), keytorestore);

            aux = NULL;
        }
    }
}

/*
//  Violation Functions
*/


int Calculate(tp aux){
    if(aux == Tnill){
        return 0;
    }
    else{
        int assert_r = 0, assert_l = 0;

        if(aux -> color == 'R'){
            assert_l = Calculate(aux -> l);
            assert_r = Calculate(aux ->r);

            if(assert_l == assert_r){
                return assert_l;
            }
            else{
                printf("\nParabiash kanona 4 sto kombo %d, l = %d, r = %d", aux -> key, assert_l, assert_r);
                return -100;
            }
        }
        else if(aux -> color == 'B'){
            assert_l = 1 + Calculate(aux -> l);
            assert_r = 1 + Calculate(aux ->r);

            if(assert_l == assert_r){
                return assert_l;
            }
            else{
                printf("\nParabiash kanona 4 sto kombo %d, l = %d, r = %d", aux -> key, assert_l, assert_r);
                return -100;
            }
        }
        else{
            return -25431;
        }
    }
}

void Violation_Of_Rule_Number_3(tp root){
    if(root != Tnill){
        Violation_Of_Rule_Number_3(root -> l);

        if(root -> color == 'R' && (root -> l -> color == 'R' || root -> r -> color == 'R'))
            printf("\nPARABIASH KANONA 3 STO KOMBO %d", root -> key);


        Violation_Of_Rule_Number_3(root -> r);
    }
}

void Violation_Of_Rule_Number_4(tp root){
    int number_of_black_nodes_in_r = 0, number_of_black_nodes_in_l = 0;

    number_of_black_nodes_in_r = Calculate(root -> r);
    number_of_black_nodes_in_l = Calculate(root -> l);

    if(number_of_black_nodes_in_l != number_of_black_nodes_in_r)
        printf("\nPARABIASH KANONA 4");
    else
        printf("\nl value %d, r value %d", number_of_black_nodes_in_l, number_of_black_nodes_in_r);
}
