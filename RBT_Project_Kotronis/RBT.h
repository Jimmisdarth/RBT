#ifndef RBT_H_INCLUDED
#define RBT_H_INCLUDED


typedef struct Tree* RedBlackTree;

/*
 * Epistrefei enan pointer typou *struct Tree wste na dhmiourgeithei mia domh
 * typou Red Black Tree.
 *
 * Ean den kataferei na ginei to allocation tou pointer tote exoume runtime error.
 */
RedBlackTree RBT_New();

/*
 * Ean to RedBlackTree rbt den exei stoixeia tote ginetai free kai h synarthsh
 * epistrefei th timh 1 alliws den ginetai h diagrafh kai epistrefei 0.
 */
int RBT_Free(RedBlackTree rbt);

/*
 * Epistrefei th time 0 ean to rbt den exei stoixeia kai th timh 1
 * ean auto den einai adeio.
 */
int RBT_isEmpty(const RedBlackTree rbt);

/*
 * Xrhsimopoeitai wste na ektypwsei to dentro pou anaparistatai apo rbt se dyo
 * diastaseis wste na fainetai eukola h domh tou.
 *
 * Xreiazetai ws orisma ena deikth se synarthsh pou na mporei na typwsei to kleidi
 * pou antistoixei sto dentro.
 */
void RBT_print2D(const RedBlackTree rbt, void (*PrintFunction)(const void *item));

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
                int (*isEqual)(const void* item1, const void* item2));

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
void RBT_Insert(RedBlackTree rbt, void *data, int (*isLessThan)(const void* item1, const void* item2));

/*
 * Diagrafei ton KOMBO tou rbt me kleidi pou antistoixei sto *data_to_delete
 * kai DEN diagrafei to idio to kleidi.
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
 * rbt exoume runtime error.
 */
int RBT_Delete(RedBlackTree rbt, void *data_to_delete,
               int (*isLessThan)(const void* item1, const void* item2),
               int (*isEqual)(const void* item1, const void* item2));

#endif // RBT_H_INCLUDED
