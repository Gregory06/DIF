#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <assert.h>

#define Oper(name, sym, num) \
        CONST_##name = num,

enum {

#include "Operators.h"

    DataSize = 20,
    StrLenth = 50,
    NotaDot = -666,
    Exp = 20

};

const char * str = NULL;
int p = 0;

#undef Oper

struct Content {

    int Type = 0;

    int DataInt = 0;

    char DataChar[StrLenth] = {};

};


struct Tree {

    Tree * Left = NULL;

    Tree * Right = NULL;

    Content Inside;

};

#include "Func_names.h"


int OhMyGodGlobalVar = 0;

Tree * GetG0(const char * s);
Tree * GetFun();
Tree * GetS();
Tree * GetE();
Tree * GetF();
Tree * GetT();
Tree * GetP();
Tree * GetN();
Tree * GetID();
Tree * GetSin();
Tree * GetLog();

Tree * CleanTree(Tree * Node);

int main() {

    Tree *Node = NULL;

    char str[30] = {};

    FILE *file = NULL;
    file = fopen("/Users/MyMac/CLionProjects/TopProgramming/Difffff/1.txt", "r");

    fscanf(file, "%s", str);

    Node = CleanTree(GetG0(str));

    OptimConst(Node);

    Node = d(Node);

    Optim(Node);

    PrintDot(Node);

    PrintInTex(Node);

//    PrintDot(Node);

    RunDot();

    return 0;

}

#include "Funcs.h"
