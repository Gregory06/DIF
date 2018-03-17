//
// Created by Greg Postnikoff on 20.11.17.
//

#ifndef DIFFFFF_FUNC_NAMES_H
#define DIFFFFF_FUNC_NAMES_H




Tree * AddNode(Tree * Node, char * Data);
int PrintTree(Tree * Node);
Tree * LoadTree(Tree * Node, FILE * file);
int FindChar(Tree * Node);
int Branch(Tree const * Node);
int PrintTreeDot(const Tree const * Node, FILE * file);
int AddNewCharacter( Tree * Node );
int AddNewBranch( Tree * Node, char * NewCharacketr, char * Diff );
int SaveTree( Tree * Node, FILE * fileS );
int TreeConstr (Tree * Node);
Tree operator * (Tree a, Tree b);
Tree * d ( Tree * Node );
Tree operator / (Tree a, Tree b);
Tree operator + (Tree a, Tree b);
Tree operator - (Tree a, Tree b);
Tree pow (Tree a, Tree b );
Tree log (Tree a);
Tree sin (Tree a);
Tree cos (Tree a);
Tree Diff_plus( Tree * Node);
Tree Diff_num ( Tree * Node );
Tree Diff_var ( Tree * Node );
Tree Diff_mul ( Tree * Node );
Tree Diff_dev ( Tree * Node );
Tree Diff_minus( Tree * Node);
Tree Diff_pow( Tree * Node);
Tree Diff_exp ( Tree * Node );
Tree Diff_numPow ( Tree * Node );
Tree Diff_varPow ( Tree * Node );
Tree Diff_log ( Tree * Node );
Tree Diff_sin ( Tree * Node );
Tree Diff_cos ( Tree * Node );
Tree * TreeCpy(Tree b);
int NullOptimMul(Tree * Node);
int UnoOptimMul(Tree * Node);
int NullOptimAdd(Tree * Node);
int OptimConst(Tree * Node);
int NullOptimMinusL(Tree * Node);
int NullOptimMinusR(Tree * Node);
int Optim(Tree * Node);
int Count(Tree * Node);
int PrintInTex(const Tree const * Node);
int PrintDot(const Tree * Node);
int RunDot();


#endif //DIFFFFF_FUNC_NAMES_H
