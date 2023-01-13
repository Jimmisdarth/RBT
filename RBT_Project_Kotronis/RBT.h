#ifndef RBT_H_INCLUDED
#define RBT_H_INCLUDED

typedef struct Node *tp;  //rbt red black tree
struct Node{
    int key;
    char color;   //M gia mauro R gia kokkino
    tp p, l, r;
} Node;

struct RBT{
    tp Root_of_Tree;
};

struct RBT *RBT_New();

void RBT_Free(struct RBT *rbt);

void RBT_print2D(tp root);

void RBT_Search(tp root, int data);

void RBT_Insert(tp *root, int data);

void RBT_Delete(tp *Treeroot, tp *root, int data);

void Violation_Of_Rule_Number_3(tp root);
void Violation_Of_Rule_Number_4(tp root);



#endif // RBT_H_INCLUDED
