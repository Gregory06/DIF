//
// Created by Greg Postnikoff on 20.11.17.
//

#ifndef DIFFFFF_FUNCS_H
#define DIFFFFF_FUNCS_H


#define Oper(name, sym, num) \
        if (( strcmp ( str, #sym ) == 0 ) && ( Node ))  \
            Node->Inside.Type = CONST_##name; \

Tree * LoadTree(Tree * Node, FILE * file) {

    char str[20] = {};
    int Input = 0;

    if (!feof(file)) {

        fscanf(file, "%s", str);

        if (!strcmp(str, "(")) {

            Node = (Tree *) calloc(1, sizeof(Tree));

            if (fscanf(file, "%d", &Input))
                Node->Inside.DataInt = Input;
            else
                fscanf(file, "%s", str);

            Node->Inside.Type = CONST_num;

#include "Operators.h"

            Node->Left = NULL;
            Node->Right = NULL;

            fscanf(file, "%[ ]", str);

            if ( fscanf(file, "%[)]", str) == 0 ) {
                Node->Left = LoadTree(Node->Left, file);
                Node->Right = LoadTree(Node->Right, file);
            }
            fscanf(file, "%[ )\n]", str);


        }
    }
    return Node;

}

#undef Oper




int Branch(const Tree const * Node) {

    return Node->Left && Node->Right;

}




#define Oper(name, sym, num) \

int PrintTreeDot(const Tree const * Node, FILE * file) {


    if (Node){
        if (Node->Left) {
            PrintTreeDot(Node->Left, file);
            fprintf(file, "\"%d\\n %d\\n %p\" -> \"%d\\n %d\\n %p\"\n", Node->Inside.DataInt, Node->Inside.Type, Node, Node->Left->Inside.DataInt, Node->Left->Inside.Type, Node->Left);
        }
        if (Node->Right) {
            PrintTreeDot(Node->Right, file);
            fprintf(file, "\"%d\\n %d\\n %p\" -> \"%d\\n %d\\n %p\"\n", Node->Inside.DataInt, Node->Inside.Type, Node, Node->Right->Inside.DataInt, Node->Right->Inside.Type, Node->Right);
        }
    }
    if (!Branch(Node))
        fprintf(file, "\"%d\\n %d\\n %p\"\n", Node->Inside.DataInt, Node->Inside.Type, Node);


    return 0;

}

int PrintDot(const Tree * Node) {

    FILE * file = NULL;

    system("mv /Users/MyMac/CLionProjects/TopProgramming/Difffff/1.gv /Users/MyMac/CLionProjects/TopProgramming/Difffff/123.txt");

    file = fopen("/Users/MyMac/CLionProjects/TopProgramming/Difffff/123.txt", "w");

    fprintf(file, "digraph G {\n");

    PrintTreeDot(Node, file);

    fprintf(file, "}");

    fclose(file);

    system("mv /Users/MyMac/CLionProjects/TopProgramming/Difffff/123.txt /Users/MyMac/CLionProjects/TopProgramming/Difffff/1.gv");

    return 0;

}

int RunDot() {

    system("open /Users/MyMac/CLionProjects/TopProgramming/Difffff/1.gv");

}


#define Oper(name, sym, num) \
        if ( Node->Inside.Type == CONST_##name ) \
            * NodeCpy = Diff_##name ( Node );

Tree * d ( Tree * Node ) {

    Tree * NodeCpy = (Tree *) calloc(1, sizeof(Tree));

#include "Operators.h"

    return  NodeCpy;

}

#undef Oper




int TreeConstr (Tree * Node) {

    Node->Left = Node->Right = NULL;

    return 0;
}




Tree Diff_dev(Tree * Node) {

    return ((* d(Node->Left) *  * Node->Right) - (* d (Node->Right) * * Node->Left)) / (* Node->Right * * Node->Right);

}

Tree Diff_mul( Tree * Node ) {

    return ( * d (Node->Left) * * Node->Right + * Node->Left * * d (Node->Right) );

}

Tree Diff_var ( Tree * Node ) {

    Tree * var = (Tree *) calloc(1, sizeof(Tree));

    TreeConstr(var);

    var->Inside.DataInt = 1;

    var->Inside.Type = CONST_num;

    return * var;

}

Tree Diff_plus( Tree * Node) {

    return * d(Node->Left) + * d (Node->Right);

}

Tree Diff_minus( Tree * Node) {

    return * d(Node->Left) - * d (Node->Right);

}

Tree Diff_num ( Tree * Node ) {

    Tree * num = (Tree *) calloc(1, sizeof(Tree));

    TreeConstr(num);

    num->Inside.DataInt = 0;

    num->Inside.Type = CONST_num;

    return * num;

}

Tree Diff_log ( Tree * Node ) {


    return * d(Node->Left) / * Node->Left;

}

Tree Diff_sin ( Tree * Node ) {

    return  cos(* Node->Left) * * d(Node->Left);

}

Tree Diff_cos (Tree * Node) {

    return  sin(* Node->Left) * * d(Node->Left);

}

Tree Diff_pow ( Tree * Node ) {

    if ((Node->Left->Inside.Type != CONST_num) && (Node->Right->Inside.Type != CONST_num))
        return Diff_exp(Node);
    else
    if (Node->Left->Inside.Type == CONST_num)
        return Diff_varPow(Node);
    else
        return Diff_numPow(Node);


}

Tree Diff_exp ( Tree * Node ) {

    Tree * mul = (Tree *) calloc(1, sizeof(Tree));

    * mul = * Node->Right * log(* Node->Left);

    Tree * exp = (Tree *) calloc(1, sizeof(Tree));

    exp->Left = exp->Right = NULL;

    exp->Inside.Type = Exp;

    return * d(mul) * pow(*exp, *mul);

}

Tree Diff_numPow ( Tree * Node ) {


    Tree * exp = (Tree *) calloc(1, sizeof(Tree));

    exp->Left = exp->Right = NULL;

    exp->Inside.Type = CONST_num;
    exp->Inside.DataInt = 1;

    return * Node->Right * pow(* Node->Left, * Node->Right - * exp ) * * d(Node->Left);

}

Tree Diff_varPow ( Tree * Node ) {

    return * d(Node->Right) * * Node * log(* Node->Left);

}



Tree * TreeCpy(Tree b) {

    Tree * a = (Tree *) calloc(1, sizeof(Tree));

    if (Branch(&b))
    {
        a->Left = TreeCpy(* b.Left);
        a->Right = TreeCpy(* b.Right);
    }

    a->Inside.DataInt = b.Inside.DataInt;

    a->Inside.Type = b.Inside.Type;

    return a;

}




Tree operator * (Tree a, Tree b) {

    Tree * mul = (Tree *) calloc(1, sizeof(Tree));

    Tree * a1 = TreeCpy(a);
    Tree * b1 = TreeCpy(b);

    mul->Inside.Type = CONST_mul;
    mul->Left = a1;
    mul->Right = b1;

    return * mul;

}

Tree operator - (Tree a, Tree b) {

    Tree * minus = (Tree *) calloc(1, sizeof(Tree));

    Tree * a1 = TreeCpy(a);
    Tree * b1 = TreeCpy(b);

    minus->Inside.Type = CONST_minus;
    minus->Left = a1;
    minus->Right = b1;

    return * minus;

}

Tree operator + (Tree a, Tree b) {

    Tree * plus = (Tree *) calloc(1, sizeof(Tree));

    Tree * a1 = TreeCpy(a);
    Tree * b1 = TreeCpy(b);

    plus->Inside.Type = CONST_plus;
    plus->Left = a1;
    plus->Right = b1;

    return * plus;

}

Tree operator / (Tree a, Tree b){

    Tree * dev = ( Tree * ) calloc(1, sizeof(Tree));

    Tree * a1 = TreeCpy(a);
    Tree * b1 = TreeCpy(b);

    dev->Inside.Type = CONST_dev;
    dev->Left = a1;
    dev->Right = b1;

    return * dev;
}

Tree pow (Tree a, Tree b ){

    Tree * pow = ( Tree * ) calloc(1, sizeof(Tree));

    Tree * a1 = TreeCpy(a);
    Tree * b1 = TreeCpy(b);

    pow->Inside.Type = CONST_pow;
    pow->Left = a1;
    pow->Right = b1;

    return * pow;

}

Tree log (Tree a){

    Tree * pow = ( Tree * ) calloc(1, sizeof(Tree));

    Tree * a1 = (Tree *) calloc(1, sizeof(Tree));

    a1->Left = a.Left;
    a1->Inside.DataInt = a.Inside.DataInt;
    pow->Inside.Type = CONST_log;
    pow->Left = a1;
    pow->Right = a1;

    return * pow;

}

Tree sin (Tree a){

    Tree * pow = ( Tree * ) calloc(1, sizeof(Tree));

    Tree * a1 = (Tree *) calloc(1, sizeof(Tree));
    a1->Inside.Type = a.Inside.Type;
    a1->Left = a.Left;
    a1->Right = a.Right;
    a1->Inside.DataInt = a.Inside.DataInt;

    pow->Inside.Type = CONST_sin;
    pow->Left = a1;
    pow->Right = a1;

    return * pow;

}

Tree cos (Tree a){

    Tree * pow = ( Tree * ) calloc(1, sizeof(Tree));

    Tree * a1 = (Tree *) calloc(1, sizeof(Tree));
    a1->Inside.Type = a.Inside.Type;
    a1->Left = a.Left;
    a1->Right = a.Right;
    a1->Inside.DataInt = a.Inside.DataInt;

    pow->Inside.Type = CONST_cos;
    pow->Left = a1;
    pow->Right = a1;

    return * pow;

}


int Optim(Tree * Node) {

    OhMyGodGlobalVar = 1;

    while (OhMyGodGlobalVar != 0) {

        OhMyGodGlobalVar = 0;

        NullOptimMul(Node);
//        UnoOptimMul(Node);
//        NullOptimAdd(Node);
        OptimConst(Node);
        NullOptimMinusL(Node);
        NullOptimMinusR(Node);

    }

    return 0;

}

int OptimConst(Tree * Node) {

    if (Node) {

        if (Node->Inside.Type > CONST_var){

            OptimConst(Node->Left);

            OptimConst(Node->Right);

            if ((Node->Left) && (Node->Right))
                if ((Node->Left->Inside.Type == CONST_num) &&
                    (Node->Right->Inside.Type == CONST_num))
                {
                    Count(Node);
                    Node->Left = Node->Right = NULL;
                    Node->Inside.Type = CONST_num;
                    OhMyGodGlobalVar++;
                }
        }
    }
}

int NullOptimMul(Tree * Node) {

    if (Node) {

        NullOptimMul(Node->Left);

        if (Node->Inside.Type == CONST_mul)
            if (((Node->Left->Inside.Type == CONST_num) && (Node->Left->Inside.DataInt == 0)) ||
                ((Node->Right->Inside.Type == CONST_num) && (Node->Right->Inside.DataInt == 0)))
            {
                Node->Inside.DataInt = 0;
                Node->Inside.Type = CONST_num;
                Node->Left = Node->Right = NULL;
                OhMyGodGlobalVar++;
            }

        NullOptimMul(Node->Right);
    }

    return 0;
}

int UnoOptimMul(Tree * Node) {

    if (Node)
    {

        UnoOptimMul(Node->Left);
        UnoOptimMul(Node->Right);

        if (Node->Inside.Type == CONST_mul)
        {
            if ((Node->Left->Inside.Type == CONST_num) && (Node->Left->Inside.DataInt == 1))
            {
                if (Node->Right)
                {
                    Node->Left = Node->Right->Left;

                    Node->Right = Node->Right->Right;
                    Node->Inside.Type = Node->Right->Inside.Type;
                    Node->Inside.DataInt = Node->Right->Inside.DataInt;
                    strcpy(Node->Inside.DataChar, Node->Right->Inside.DataChar);
                }
//                Node = TreeCpy(* Node->Right);
                OhMyGodGlobalVar++;
            }
            else
                if ((Node->Right->Inside.Type == CONST_num) && (Node->Right->Inside.DataInt == 1))
                {
                    if (Node->Left) {
                        Node->Left = Node->Left->Left;
                        Node->Right = Node->Left->Right;
                        Node->Inside.Type = Node->Left->Inside.Type;
                        Node->Inside.DataInt = Node->Left->Inside.DataInt;
                        strcpy(Node->Inside.DataChar, Node->Left->Inside.DataChar);
                    }
//                    Node = TreeCpy(* Node->Left);
                    OhMyGodGlobalVar++;
                }
        }


    }

    return 0;
}

int NullOptimAdd(Tree * Node) {

    if (Node) {

        NullOptimAdd(Node->Left);
        NullOptimAdd(Node->Right);

        if (Node->Inside.Type == CONST_plus)
        {
            if ((Node->Left->Inside.Type == CONST_num) && (Node->Left->Inside.DataInt == 0))
            {
                Node->Left = Node->Right->Left;
                Node->Right = Node->Right->Right;
                Node->Inside.Type = Node->Right->Inside.Type;
                Node->Inside.DataInt = Node->Right->Inside.DataInt;
                //Node = TreeCpy(*Node->Right);
                OhMyGodGlobalVar++;
            }
            else
                if ((Node->Right->Inside.Type == CONST_num) && (Node->Right->Inside.DataInt == 0))
                {
                    Node->Left = Node->Left->Left;
                    Node->Right = Node->Left->Right;
                    Node->Inside.Type = Node->Left->Inside.Type;
                    Node->Inside.DataInt = Node->Left->Inside.DataInt;
//                    Node = TreeCpy(*Node->Left);
                    OhMyGodGlobalVar++;
                }
        }

    }

    return 0;

}

int NullOptimMinusR(Tree * Node) {

    if (Node) {

        NullOptimMinusR(Node->Left);

        if (Node->Inside.Type == CONST_minus)
        {
            if ((Node->Right->Inside.Type == CONST_num) && (Node->Right->Inside.DataInt == 0)) {
                Node = TreeCpy(* Node->Left);
                OhMyGodGlobalVar++;
            }
        }

        NullOptimMinusR(Node->Right);
    }

    return 0;
}

int NullOptimMinusL(Tree * Node) {

    if (Node) {

        NullOptimMinusR(Node->Left);

        if (Node->Inside.Type == CONST_minus)
        {
            if ((Node->Left->Inside.Type == CONST_num) && (Node->Left->Inside.DataInt == 0)) {
                Node->Left->Inside.DataInt = -1;
                Node->Inside.Type == CONST_mul;
                OhMyGodGlobalVar++;
            }
        }

        NullOptimMinusR(Node->Right);
    }

    return 0;
}

int Count(Tree * Node) {

    switch (Node->Inside.Type){
        case 1:
            Node->Inside.DataInt = Node->Left->Inside.DataInt + Node->Right->Inside.DataInt;
            break;
        case 2:
            Node->Inside.DataInt = Node->Left->Inside.DataInt - Node->Right->Inside.DataInt;
            break;
        case 3:
            Node->Inside.DataInt = Node->Left->Inside.DataInt / Node->Right->Inside.DataInt;
            break;
        case 4:
            Node->Inside.DataInt = Node->Left->Inside.DataInt * Node->Right->Inside.DataInt;
            break;
        case 5:
            Node->Inside.DataInt = Node->Left->Inside.DataInt + Node->Right->Inside.DataInt;
            break;
    }

    return 0;

}




int PrintInTex(const Tree const * Node) {

    if (Node)
        if (Node->Inside.Type == CONST_mul)
        {
            if ((Node->Left->Inside.Type == CONST_num) && (Node->Right->Inside.Type == CONST_var))
                printf("%dx", Node->Left->Inside.DataInt);
            else
                if ((Node->Right->Inside.Type == CONST_num) && (Node->Left->Inside.Type == CONST_var))
                    printf("%dx", Node->Right->Inside.DataInt);
                else {
                    PrintInTex(Node->Left);
                    printf(" \\cdot ");
                    PrintInTex(Node->Right);
                }
        } else
        if (Node->Inside.Type == CONST_dev)
        {
            printf(" \\frac{");
            PrintInTex(Node->Left);
            printf("}{");
            PrintInTex(Node->Right);
            printf("}");
        } else {
            if ((Node) &&
                    ((Node->Inside.Type == CONST_log) ||
                            ((Node->Inside.Type == CONST_cos)) ||
                    (Node->Inside.Type == CONST_sin))) {
                switch (Node->Inside.Type) {
                    case CONST_sin:
                        printf("sin");
                        break;
                    case CONST_cos:
                        printf("cos");
                        break;
                    case CONST_log:
                        printf("log");
                        break;
                }

                if (Node->Left) {
                    printf("(");
                    PrintInTex(Node->Left);
                    printf(")");
                }
            } else {

                if (Node->Inside.Type == CONST_pow) {
                    PrintInTex(Node->Left);
                    printf("^");
                    printf("{");
                    PrintInTex(Node->Right);
                    printf("}");
                } else {

                    if (Node->Left) {
                        printf("(");
                        PrintInTex(Node->Left);
                    }

                    switch (Node->Inside.Type) {
                        case CONST_plus:
                            printf("+");
                            break;
                        case CONST_minus:
                            printf("-");
                            break;
                        case CONST_var:
                            printf("x");
                            break;
                        case CONST_num:
                            printf("%d", Node->Inside.DataInt);
                            break;
                        case Exp:
                            printf("e");
                            break;

                    }

                    if (Node->Right) {
                        PrintInTex(Node->Right);
                        printf(")");
                    }
                }
            }

        }

}

Tree * GetN()
{
    int val = 0;
    while (str[p] >= '0' && str[p] <= '9')
    {
        val = val * 10 + str[p] - '0';
        p++;
    }

    Tree * Val = (Tree *) calloc(1, sizeof(Tree));

    Val->Right = Val->Left = NULL;

    Val->Inside.Type = CONST_num;
    Val->Inside.DataInt = val;

    return Val;

}

Tree * GetLog()
{

    char var[StrLenth] = {};
    int i = 0;
    while (isalpha(str[p+i]))
    {
        var[i] = str[p+i];
        i++;
    }

    Tree * Val = (Tree *) calloc(1, sizeof(Tree));

    if (strcmp(var, "log") == 0)
    {

        p += 3;

        Val->Right = NULL;
        Val->Left = GetP();

        Val->Inside.Type = CONST_log;

    }

    return Val;

}

Tree * GetSin()
{

    char var[StrLenth] = {};
    int i = 0;
    while (isalpha(str[p+i]))
    {
        var[i] = str[p+i];
        i++;
    }

    Tree * Val = (Tree *) calloc(1, sizeof(Tree));

    if (strcmp(var, "sin") == 0)
    {

        p += 3;
//        Val->Right = NULL;
        Val->Left = GetP();
        Val->Right = Val->Left;

        Val->Inside.Type = CONST_sin;

    }

    if (strcmp(var, "cos") == 0)
    {

        p += 3;
//        Val->Right = NULL;
        Val->Left = GetP();
        Val->Right = Val->Left;

        Val->Inside.Type = CONST_cos;

    }

    return Val;

}

Tree * GetID() {

    char var[StrLenth] = {};
    int i = 0;
    while (isalpha(str[p]))
    {
        var[i] = str[p];
        p++;
        i++;
    }

    Tree * Val = (Tree *) calloc(1, sizeof(Tree));

    Val->Right = Val->Left = NULL;

    Val->Inside.Type = CONST_var;
    strcpy(Val->Inside.DataChar,var);

    return Val;
}

Tree * GetP()
{
    Tree * Val = (Tree *) calloc(1, sizeof(Tree));

    if (str[p] == '(')
    {
        p++;
        Val = GetE();
        assert(str[p] == ')');
        p++;
        return Val;
    }
    else
    {
        int check = p;
        Val = GetN();
        if (check == p) {
            Val = GetLog();
            if (check == p) {
                Val = GetSin();
                if (check == p)
                    return GetID();
                else
                    return Val;
            } else
                return Val;
        }
        else
            return Val;

    }
}



Tree * GetF()
{
    Tree * Dot = (Tree *) calloc(1, sizeof(Tree));
    Dot->Inside.Type = NotaDot;
    Dot->Left = GetP();

    while (str[p] == '^')
    {
        int Oper = str[p];
        p++;
        if (Dot->Right)
        {
            Tree * Dot1 = (Tree *) calloc(1, sizeof(Tree));
            Dot1->Left = Dot->Right;
            Dot1->Right = GetP();
            Dot->Right = Dot1;
            Dot1->Inside.Type = CONST_pow;

        } else
        {
            Dot->Right = GetP();

            Dot->Inside.Type = CONST_pow;
        }
    }

    return Dot;

}



Tree * GetT()
{
    Tree * Dot = (Tree *) calloc(1, sizeof(Tree));
    Dot->Inside.Type = NotaDot;
    Dot->Left = GetF();

    while (str[p] == '*' || str[p] == '/')
    {
        int Oper = str[p];
        p++;
        if (Dot->Right)
        {
            Tree * Dot1 = (Tree *) calloc(1, sizeof(Tree));
            Dot1->Left = Dot->Right;
            Dot1->Right = GetF();
            Dot->Right = Dot1;
            if (Oper == '*')
                Dot1->Inside.Type = CONST_mul;
            else
                Dot1->Inside.Type = CONST_dev;
        } else
        {
            Dot->Right = GetF();
            if (Oper == '*')
                Dot->Inside.Type = CONST_mul;
            else
                Dot->Inside.Type = CONST_dev;
        }
    }

    return Dot;

}

Tree * GetE()
{
    Tree * Dot = (Tree *) calloc(1, sizeof(Tree));
    Dot->Left = GetT();
    Dot->Inside.Type = NotaDot;

    while (str[p] == '+' || str[p] == '-')
    {
        int Oper = str[p];
        p++;
        if (Dot->Right)
        {
            Tree * Dot1 = (Tree *) calloc(1, sizeof(Tree));
            Dot1->Left = Dot->Right;
            Dot1->Right = GetT();
            Dot->Right = Dot1;
            if (Oper == '+')
                Dot1->Inside.Type = CONST_plus;
            else
                Dot1->Inside.Type = CONST_minus;
        } else
        {
            Dot->Right = GetT();
            if (Oper == '+')
                Dot->Inside.Type = CONST_plus;
            else
            if (Oper == '-')
                Dot->Inside.Type = CONST_minus;
        }
    }

    return Dot;

}

Tree * GetG0(const char * what)
{
    Tree * Dot = (Tree *) calloc(1, sizeof(Tree));
    Dot->Inside.Type = NotaDot;

    str = what;
    p = 0;
    Dot->Left = GetE();

    assert(str[p] == 0);

    return Dot;

}

Tree * CleanTree(Tree * Node) {

    if (Node) {

        while(Node->Inside.Type == NotaDot)
            Node = Node->Left;

        if (Node->Left)
            while (Node->Left->Inside.Type == NotaDot)
                Node->Left = Node->Left->Left;
        if (Node->Right)
            while (Node->Right->Inside.Type == NotaDot)
                Node->Right = Node->Right->Left;

        if (Node->Right)
            CleanTree(Node->Right);
        if (Node->Left)
            CleanTree(Node->Left);
    }

    return Node;

}

#endif //DIFFFFF_FUNCS_H
