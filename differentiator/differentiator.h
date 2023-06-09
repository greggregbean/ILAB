#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <cmath>

enum types
{
    NUM = 'n',
    VAR = 'v',
    ADD = '+',
    DIV = '-',
    POW = '^',
    MUL = '*',
    SUB = '/'
};

union value
{
    char varOrOper;
    double number;
};

struct treeEl
{
    value val;
    int type;
    treeEl* left;
    treeEl* right;
};

class tree
{
    private:
        treeEl* head_;

    public:
        tree();
        void textDump();
        void graphDump(FILE* filep);
        void reader(FILE* filep);
        void treeCopy();
        void differentiator();
};

//DUMP:
void recursiveGraph(FILE* filep, treeEl* node);
void recursiveDump(treeEl* node, treeEl* head);
void nodeDump(treeEl* node);
void fprintVal(FILE* filep, treeEl* node);
void printVal(treeEl* node);

//НАДО ДОРАБОТАТЬ
/*void AddDivDump(treeEl* node);
void MulSubDump(treeEl* node);
void PowDump(treeEl* node);
void VarNumDump(treeEl* node);*/

//READER:
void spaceSkip(FILE* filep);
treeEl* MainParse(FILE* filep);
treeEl* AddDivParse(FILE* filep);
treeEl* MulSubParse(FILE* filep);
treeEl* VarNumParse(FILE* filep);
treeEl* PowParse(FILE* filep);

//DIFFERENTIATOR:
treeEl* nodeToNum(treeEl* node, int num);
treeEl* recursiveCopy(treeEl* node);
treeEl* newTreeEl(int type, value val, treeEl* left, treeEl* right);
treeEl* recursiveDif(treeEl* node);

#endif