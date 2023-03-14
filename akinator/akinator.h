#ifndef AKINATOR_H
#define AKINATOR_H

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define FOUND 1
#define NOTFOUND 0
#define PHRASEMAXLEN 50
#define TREEBUFLEN 1000

struct treeEl
{
    char* phrase;
    treeEl* yes;
    treeEl* no;
};

class tree
{
    private:
        treeEl* head_;

    public:
        tree();
        void textDump();
        void graphDump(FILE* filep);
        void fileDump(FILE* filep);
        void reader(FILE* textTree);
        treeEl* akinator();
};

void spaceSkip(FILE* filep);
void recursiveDump(treeEl* node);
void recursiveGraph(FILE* filep, treeEl* node);
void recursiveFileDump(FILE* filep, treeEl* node);
treeEl* treeInsert (char* phrase);
void liner(FILE* fp, char* treeBuf);
treeEl* recursiveReader(char* treeBuf, int* index);

#endif