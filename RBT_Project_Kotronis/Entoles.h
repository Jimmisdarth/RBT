#ifndef ENTOLES_H_INCLUDED
#define ENTOLES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "RBT.h"
#include "IntModule.h"
#include "StringModule.h"

#define SIZE_OF_STRING 5

void PrintMenu();
void Print(const RedBlackTree rbt_int, const RedBlackTree rbt_string);
void Insert(RedBlackTree rbt_int, RedBlackTree rbt_string);
void Find(const RedBlackTree rbt_int, const RedBlackTree rbt_string);
void Delete(RedBlackTree rbt_int, RedBlackTree rbt_string);
void Clear(RedBlackTree rbt_int, RedBlackTree rbt_string);
void isEmpty(const RedBlackTree rbt_int, const RedBlackTree rbt_string);

#endif // ENTOLES_H_INCLUDED
