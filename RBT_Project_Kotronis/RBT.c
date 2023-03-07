#include "RBT.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define COUNT 15

typedef struct Node* node_pointer;
struct Node{
    void* key;
    char color;     // M gia mauro R gia kokkino
    node_pointer p; // Parent
    node_pointer l; // Left child
    node_pointer r; // Right child
} Node;

struct Tree{
    node_pointer Root;
    node_pointer Tnill;
};


node_pointer RBT_initialize_nill();
node_pointer RBT_initialize_node(RedBlackTree rbt, void *new_data);

void RBT_print2DUtil(const node_pointer x, const node_pointer nill, int space,
                 void (*PrintFunction)(const void *item));

node_pointer RBT_findnode(const RedBlackTree rbt, const void* data,
                      int (*isLessThan)(const void* item1, const void* item2),
                      int (*isEqual)(const void* item1, const void* item2));

void RBT_LeftRotate(RedBlackTree rbt, node_pointer x);
void RBT_RightRotate(RedBlackTree rbt, node_pointer x);

void RBT_Insert_FixUp(RedBlackTree rbt, node_pointer z);

void RBT_Transplant(RedBlackTree rbt, node_pointer u, node_pointer v);
node_pointer RBT_Tree_Minimum(RedBlackTree rbt, node_pointer x);
void RBT_RB_Delete(RedBlackTree rbt, node_pointer z);
void RBT_Delete_Fixup(RedBlackTree rbt, node_pointer x);

void RBT_CheckForViolation(const RedBlackTree rbt);
int RBT_Calculate(const RedBlackTree rbt, node_pointer aux);
void RBT_Violation_Of_Rule_Number_3(const RedBlackTree rbt, node_pointer root, int *error);
int  RBT_Violation_Of_Rule_Number_4(const RedBlackTree rbt, node_pointer root);


/**
***  Initialize Functions
**/

/*
 * Epistrefei enan pointer se struct Node me orismenes arxikes times wste na
 * oristei ws o Tnill kombos tou dentrou.
 *
 * Ean den kataferei na ginei to allocation tou pointer tote exoume runtime error.
 */
node_pointer RBT_initialize_nill(){
    node_pointer nill_pointer = (node_pointer)malloc(sizeof(struct Node));
    assert(nill_pointer != NULL);

    nill_pointer -> p = NULL;
    nill_pointer -> l = NULL;
    nill_pointer -> r = NULL;
    nill_pointer -> key = NULL;
    nill_pointer -> color = 'B';

    return nill_pointer;
}

/*
 * Epistrefei enan pointer se struct Node me kathorismenes arxikes times me kleidi
 * ton pointer new_data.
 *
 * Ean den kataferei na ginei to allocation tou pointer tote exoume runtime error.
 */
node_pointer RBT_initialize_node(RedBlackTree rbt, void *new_data){
    node_pointer new_pointer = (node_pointer)malloc(sizeof(struct Node));
    assert(new_pointer != NULL);

    new_pointer -> p = rbt -> Tnill;
    new_pointer -> l = rbt -> Tnill;
    new_pointer -> r = rbt -> Tnill;
    new_pointer -> key = new_data;
    new_pointer -> color = 'R';

    return new_pointer;
}

/*
 * Epistrefei enan pointer typou *struct Tree wste na dhmiourgeithei mia domh
 * typou Red Black Tree.
 *
 * Ean den kataferei na ginei to allocation tou pointer tote exoume runtime error.
 */
RedBlackTree RBT_New(){
    RedBlackTree rbt = (RedBlackTree)malloc(sizeof(struct Tree));
    assert(rbt != NULL);

    rbt -> Tnill = RBT_initialize_nill();
    rbt -> Root = rbt -> Tnill;

    return rbt;
}

/*
 * Ean to RedBlackTree rbt den exei stoixeia tote ginetai free kai h synarthsh
 * epistrefei th timh 1 alliws den ginetai h diagrafh kai epistrefei 0.
 *
 */
int RBT_Free(RedBlackTree rbt){
    if(RBT_isEmpty(rbt)){
        free(rbt);
        return 1;
    }

    return 0;
}

/**
***  Print Functions
**/

/*
 * Typwnei to dentro me disdiasto tropo wste na einai eukola emfanhs h domh tou.
 */
void RBT_print2DUtil(const node_pointer x, const node_pointer nill, int space,
                 void (*PrintFunction)(const void *item))
{
    // Base case
    if (x == nill)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    RBT_print2DUtil(x -> r, nill, space, PrintFunction);

    // Print current node after space
    // count
    printf("\n");
    int i;
    for (i = COUNT; i < space; i++)
        printf(" ");
    PrintFunction(x -> key);
    printf(" %c\n", x -> color);

    // Process left child
    RBT_print2DUtil(x -> l, nill, space, PrintFunction);
}

/*
 * Wrapper gia thn RBT_print2DUtil() xrhsimopoeitai wste na ektypwsei to dentro pou
 * anaparistatai apo to RedBlackTree rbt se dyo diastaseis wste na fainetai
 * eukola h domh tou.
 *
 * Xreiazetai ws orisma ena deikth se synarthsh pou na mporei na typwsei to kleidi
 * pou antistoixei sto dentro.
 */
void RBT_print2D(const RedBlackTree rbt, void (*PrintFunction)(const void *item))
{
    if(!RBT_isEmpty(rbt)){
        // Pass initial space count as 0
        RBT_print2DUtil(rbt -> Root, rbt -> Tnill, 0, PrintFunction);
    }
    else{
        printf("\nTo dentro den exei stoixeia\n");
    }

}

/**
***  Find Functions
**/

/*
 * Epistrefei enan deikth pou theixnei sto kombou tou dentrou pou exei kleidi iso
 * me auto pou antistoixei sto (void *data).
 *
 * Ean den brethei to kleidi tote epistrefei to Tnill.
 */
node_pointer RBT_findnode(const RedBlackTree rbt, const void* data,
                      int (*isLessThan)(const void* item1, const void* item2),
                      int (*isEqual)(const void* item1, const void* item2))
{
    node_pointer x = rbt -> Root;

    while(x != rbt -> Tnill && (!isEqual(x -> key, data))){
       if(isLessThan(data, x -> key)){
        x = x -> l;
       }
       else{
        x = x -> r;
       }
    }

    return x;
}

/*
 * Anazhta sto RedBlackTree rbt to kleidi pou antistoixei ston deikth void* data.
 *
 * Dexetai ws orisma deikth se synarthsh (*isLessThan) opou epistrefei 1 ean to
 * to kleidi pou antistoixei sto *item1 > kleidi *item2 alliws epistrefei 0.
 *
 * Dexetai ws orisma deikth se synarthsh (*isEqual) opou epistrefei 1 ean to
 * to kleidi pou antistoixei sto *item1 == kleidi *item2 alliws epistrefei 0.
 *
 * Ean brethei to kleidi epistrefei 1 alliws epistrefei th timh 0.
 */
int RBT_Search(const RedBlackTree rbt, const void* data,
                int (*isLessThan)(const void* item1, const void* item2),
                int (*isEqual)(const void* item1, const void* item2))
{
    node_pointer x = rbt -> Root;

    while(x != rbt -> Tnill && (!isEqual(x -> key, data))){
       if(isLessThan(data, x -> key)){
        x = x -> l;
       }
       else{
        x = x -> r;
       }
    }

    if(x != rbt -> Tnill)
        return 1;
    else
        return 0;
}

/**
***  Rotation Functions
**/

/*
 * Tropopoiei to dentro RedBlackTree rbt ektelontas ena left rotation gyro
 * apo th syndesh toy x kai tou deji paidiou tou (x -> r).
 *
 * Pio analytika kai me eikones : page 312 Introduction to Algorithms 3rd Edition.
 */
void RBT_LeftRotate(RedBlackTree rbt, node_pointer x){
    node_pointer y = x -> r;    //arxikopoioume to y
    x -> r = y -> l;            //to aristero ypodentro toy y ginetai to deji ypodentro tou x

    if(y -> l != rbt -> Tnill)
        y -> l -> p = x;

    y -> p = x -> p;    //syndeoume to p tou x sto y

    if(x -> p == rbt -> Tnill)
        rbt -> Root = y;
    else if(x == x -> p -> l)
        x -> p -> l = y;
    else
        x -> p -> r = y;

    y -> l = x;     //bazoume to x sta aristera tou y
    x -> p = y;
}

/*
 * Tropopoiei to dentro RedBlackTree rbt ektelontas ena right rotation gyro
 * apo th syndesh toy x kai tou aristerou paidiou tou (x -> l).
 *
 * Pio analytika kai me eikones : page 312 Introduction to Algorithms 3rd Edition.
 */
void RBT_RightRotate(RedBlackTree rbt, node_pointer x){
    node_pointer y = x -> l;    //arxikopoioume to y
    x -> l = y -> r;            //to deji ypodentro toy y ginetai to aristero ypodentro tou x

    if(y -> r != rbt -> Tnill)
        y -> r -> p = x;

    y -> p = x -> p;    //syndeoume to p tou x sto y

    if(x -> p == rbt -> Tnill)
        rbt -> Root = y;
    else if(x == x -> p -> r)
        x -> p -> r = y;
    else
        x -> p -> l = y;

    y -> r = x;     //bazoume to x sta dejia tou y
    x -> p = y;
}

/**
***  Insert Functions
**/

/*
 * Eisagei sto dentro RedBlackTree rbt ena neo stoixeio me kleidi pou antistoixei
 * sto void *data_to_insert.
 *
 * Dexetai ws orisma deikth se synarthsh (*isLessThan) opou epistrefei 1 ean to
 * to kleidi pou antistoixei sto *item1 > kleidi *item2 alliws epistrefei 0.
 *
 * Ean to rbt einai NULL tote exoume runtime error.
 *
 * Ean meta thn eisagwgh tou stoixeiou yparxoun parabiaseis stis idiotites ths
 * domh tou rbt tote exoume runtime error.
 */
void RBT_Insert(RedBlackTree rbt, void* data_to_insert,
                int (*isLessThan)(const void* item1, const void* item2))
{ // isnertion me while loops

    assert(rbt != NULL);

    node_pointer z = RBT_initialize_node(rbt, data_to_insert);

    node_pointer y = rbt -> Tnill;
    node_pointer x = rbt -> Root;

    while(x != rbt -> Tnill){
        y = x;
        if(isLessThan(z -> key, x -> key))
            x = x -> l;
        else
            x = x -> r;
    }

    z -> p = y;

    if(y == rbt -> Tnill)
        rbt -> Root = z;
    else if(isLessThan(z -> key, y -> key))
        y -> l = z;
    else
        y -> r = z;

    RBT_Insert_FixUp(rbt, z);

    RBT_CheckForViolation(rbt);
}

/*
 * Kaleitai sto telos ths RBT_Insert wste na diorthosei tyxon parabiaseis stis
 * idiotites ths domhs tou dentrou pou mporei na exoun dhmiourghthei.
 *
 * page 308 Introduction to Algorithms 3rd Edition Properties of Red Black Tree.
 */
void RBT_Insert_FixUp(RedBlackTree rbt, node_pointer z){
    node_pointer y;
    while(z -> p -> color == 'R'){
        if(z -> p ==  z -> p -> p -> l){
            y = z -> p -> p -> r;

            if(y -> color == 'R'){  //case 1
                z -> p -> color = 'B';
                y -> color = 'B';

                z -> p -> p -> color = 'R';
                z = z -> p -> p;
            }
            else{
                if(z == z -> p -> r){   //case 2
                    z = z -> p;
                    RBT_LeftRotate(rbt, z);
                    }

                z -> p -> color = 'B';  //case 3
                z -> p -> p -> color = 'R';
                RBT_RightRotate(rbt, z -> p -> p);
            }
        }
        else{
            y = z -> p -> p -> l;

            if(y -> color == 'R'){
                z -> p -> color = 'B';
                y -> color = 'B';

                z -> p -> p -> color = 'R';
                z = z -> p -> p;
            }
            else{
                if(z == z -> p -> l){
                    z = z -> p;
                    RBT_RightRotate(rbt, z);
                }

                z -> p -> color = 'B';
                z -> p -> p -> color = 'R';
                RBT_LeftRotate(rbt, z -> p -> p);
            }
        }
    }

    rbt -> Root -> color = 'B';
}

/**
***  Delete Functions
**/

/*
 * Antikathista to ypodentro sto kombo u me to ypodentro stho kombo v analoga
 * me th thesh pou exei to u sto dentro rbt.
 */
void RBT_Transplant(RedBlackTree rbt, node_pointer u, node_pointer v){
    if(u -> p == rbt -> Tnill)
        rbt -> Root = v;
    else if(u == u -> p -> l)
        u -> p -> l = v;
    else
        u -> p -> r = v;
    v -> p = u -> p;
}

/*
 * Epistrefei enan deikth sto kombo me to mikrotero kleidi sto ypodentro tou x.
 */
node_pointer RBT_Tree_Minimum(RedBlackTree rbt, node_pointer x){
    while(x -> l != rbt -> Tnill)
        x = x -> l;

    return x;
}

/*
 * Diagrafei ton KOMBO tou rbt me kleidi pou antistoixei sto *data_to_delete
 * kai den diagrafei to idio to kleidi.
 *
 * Dexetai ws orisma deikth se synarthsh (*isLessThan) opou epistrefei 1 ean to
 * to kleidi pou antistoixei sto *item1 > kleidi *item2 alliws epistrefei 0.
 *
 * Dexetai ws orisma deikth se synarthsh (*isEqual) opou epistrefei 1 ean to
 * to kleidi pou antistoixei sto *item1 == kleidi *item2 alliws epistrefei 0.
 *
 * An de brethei o kombos tote the ginetai h diagrafh kai epistrefei th timh 0
 * Alliws ekteleitai h diagrafh kai epistrefei 1.
 *
 * Ean meta th diagrafh exei ginei kapoia parabiash stis idiothtes sth domh tou
 * rbt tote exoume runtime error.
 */
int RBT_Delete(RedBlackTree rbt, void *data_to_delete,
               int (*isLessThan)(const void* item1, const void* item2),
               int (*isEqual)(const void* item1, const void* item2))
{
    node_pointer z = RBT_findnode(rbt, data_to_delete, isLessThan, isEqual);

    if(z != rbt -> Tnill){
        RBT_RB_Delete(rbt, z);
        free(z);
        rbt -> Tnill -> p = NULL;

        RBT_CheckForViolation(rbt);
        return 1;
    }
    else
        return 0;
}

/*
 * Afairei to kombo z apo to dentro rbt ALLA DEN TO DIAGRAFEI kai epeita kalei thn
 * RBT_RB_Delete_Fixup wste na diorthosei tis parabiaseis pou mporei na ginoun
 * ean o kombos z pou afairethike eixe mauro xrwma ('B').
 */
void RBT_RB_Delete(RedBlackTree rbt, node_pointer z){
    node_pointer x;

    node_pointer y = z;
    char y_original_color = y -> color;

    if(z -> l == rbt -> Tnill){ //to aristero paidi einai nill
        x = z -> r;
        RBT_Transplant(rbt, z, z -> r);
    }
    else if(z -> r == rbt -> Tnill){    //to deji paidi einai nill **Mporei na exoume kai diagrafei fyloy edw
        x = z -> l;
        RBT_Transplant(rbt, z, z -> l);
    }
    else{   //to node exei dyo paidia
        y = RBT_Tree_Minimum(rbt, z -> r);
        y_original_color = y -> color;
        x = y -> r;

        if(y -> p == z){
            x -> p = y;
        }
        else{
            RBT_Transplant(rbt, y, y -> r);
            y -> r = z -> r;
            y -> r -> p = y;
        }

        RBT_Transplant(rbt, z, y);

        y -> l = z -> l;
        y -> l -> p = y;
        y -> color = z -> color;
    }

    if(y_original_color == 'B')
        RBT_Delete_Fixup(rbt, x);
}

/*
 * Diorthonei tis parabiaseis pou mporei na dhmiourgithkan sto rbt kata thn
 * afairesh enos kombou sthn yproutina RBT_RB_Delete.
 */
void RBT_Delete_Fixup(RedBlackTree rbt, node_pointer x){
    node_pointer w;

    while(x != rbt -> Root && x -> color == 'B'){
        if(x == x -> p -> l){   //to x einai aristero paidi
            w = x -> p -> r;

            if(w -> color == 'R'){  //case 1
                w -> color = 'B';
                x -> p -> color = 'R';

                RBT_LeftRotate(rbt, x -> p);
                w = x -> p -> r;
            }
            if(w -> l -> color == 'B' && w -> r -> color == 'B'){   //case 2
                w -> color = 'R';
                x = x -> p;
            }
            else{
                if(w -> r -> color == 'B'){ //case 3
                    w -> l -> color = 'B';
                    w -> color = 'R';

                    RBT_RightRotate(rbt, w);
                    w = x -> p -> r;
                }

                w -> color = x -> p -> color;   //case 4
                x -> p -> color = 'B';
                w -> r -> color = 'B';
                RBT_LeftRotate(rbt, x -> p);
                x = rbt -> Root;
            }
        }
        else{   //to x einai deji paidi
            w = x -> p -> l;

            if(w -> color == 'R'){  //case 1
                w -> color = 'B';
                x -> p -> color = 'R';

                RBT_RightRotate(rbt, x -> p);
                w = x -> p -> l;
            }
            if(w -> r -> color == 'B' && w -> l -> color == 'B'){   //case 2
                w -> color = 'R';
                x = x -> p;
            }
            else{
                if(w -> l -> color == 'B'){ //case 3
                    w -> r -> color = 'B';
                    w -> color = 'R';

                    RBT_LeftRotate(rbt, w);
                    w = x -> p -> l;
                }

                w -> color = x -> p -> color;   //case 4
                x -> p -> color = 'B';
                w -> l -> color = 'B';
                RBT_RightRotate(rbt, x -> p);
                x = rbt -> Root;
            }
        }
    }

    x -> color = 'B';
}

/**
***  Violation Functions
**/

/*
 * Elegxei ean exoun ginei parabiaseis ths idiothtas 3 kai 4 enos Red Black Tree
 * gia to dentro rbt. https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 * (Properties).
 *
 * Ean exei ginei parabiash se estw kai mia idiothta tote exoume runtime error.
 */
void RBT_CheckForViolation(const RedBlackTree rbt){
    //Tsekarei an exoun ginei parabiaseis

    if(!RBT_isEmpty(rbt)){
        int error1 = 0;
        RBT_Violation_Of_Rule_Number_3(rbt, rbt -> Root, &error1);
        assert(error1 == 0);

        int error2 = RBT_Violation_Of_Rule_Number_4(rbt, rbt -> Root);
        assert(error2 == 0);
    }
}

/*
 * Ypologizei posa black nodes yparxoyn sto aristero kai sto deji paidi tou aux
 *
 * Ean exoume ton idio arithmo se black nodes kai stis dyo pleures tote episttrefei
 * ton arithmo twn black nodes.
 * Eidalws epistrefei to megalytero arithmo apo tous dyo.
 */
int RBT_Calculate(const RedBlackTree rbt, node_pointer aux){
    if(aux == rbt -> Tnill){
        return 0;
    }
    else{
        int check_right = 0, check_left = 0;
        int adder = 0;

        if(aux -> color == 'B')
            adder = 1;

        check_left  = adder + RBT_Calculate(rbt, aux -> l);
        check_right = adder + RBT_Calculate(rbt, aux -> r);

        if(check_left == check_right)
            return check_left;
        else if(check_left > check_right)
            return check_right;
        else
            return check_left;
    }
}

/*
 * Elegxei olo to rbt gia to ean exei ginei parabiash tis idiothtas 3, dhladh oti
 * den mporei na yparxei Red kombos me Red paidia.
 *
 * Kathe fora pou ginetai parabiash tou kanona tote aujanetai h timh pou deixnei
 * o deikths *error kai wste na antilifthei o caller oti yparxei parabiash.
 */
void RBT_Violation_Of_Rule_Number_3(const RedBlackTree rbt, node_pointer root, int *error){
    if(root != rbt -> Tnill){
        RBT_Violation_Of_Rule_Number_3(rbt, root -> l, error);

        if(root -> color == 'R' && (root -> l -> color == 'R' || root -> r -> color == 'R'))
            ++(*error);

        RBT_Violation_Of_Rule_Number_3(rbt, root -> r, error);
    }
}

/*
 * Elegxei ean sto Root tou rbt yparxei o idios arithmos Black kombwn toso sto
 * deji oso kai sto aristero paidi (Property 4) kalwntas thn yporoutina Calculate.
 *
 * Ean ginei parabiash epistrefei th timh 1 alliws epistrefei th timh 0.
 */
int RBT_Violation_Of_Rule_Number_4(const RedBlackTree rbt, node_pointer root){
    int error = 0;
    int number_of_black_nodes_in_r = 0, number_of_black_nodes_in_l = 0;

    number_of_black_nodes_in_r = RBT_Calculate(rbt, root -> r);
    number_of_black_nodes_in_l = RBT_Calculate(rbt, root -> l);

    if(number_of_black_nodes_in_l != number_of_black_nodes_in_r)
        error = 1;

    return error;
}


/**
***  Bool Fucntions
**/

/*
 * Epistrefei th time 0 ean to rbt den exei stoixeia kai th timh 1
 * Ean auto den einai adeio.
 */
int RBT_isEmpty(const RedBlackTree rbt){
    return (rbt -> Root == rbt -> Tnill);
}
