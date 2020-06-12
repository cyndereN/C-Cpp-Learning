#include <stdio.h>
#include <stdlib.h>
 
#define ElementType char

typedef struct Node {
    ElementType data;
    struct Node *lchild;
    struct Node *rchild;
}BinaryTree;
 
//创建二叉树节点
BinaryTree* CreateBinaryTree(data) {
    BinaryTree* t = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (!t) {
        printf("空间不足！\n");
        return NULL;
    }
    t->lchild = NULL;
    t->rchild = NULL;
    t->data = data;
    return t;
}
 
/*
 (1)先序遍历 递归解法
 遍历过程为：
    1.访问根节点
    2.遍历其左子树
    3.遍历其右子树
*/
void PreOrderTraversal(BinaryTree* BT) {
    if (BT) {
        printf("%c", BT->data);
        PreOrderTraversal(BT->lchild);
        PreOrderTraversal(BT->rchild);
    }
}
 
/*
 (2)中序遍历 递归解法
 遍历过程：
    1.遍历其左子树
    2.访问根节点
    3.遍历其右子树
*/
void InOrderTraversal(BinaryTree* BT) {
    if (BT) {
        InOrderTraversal(BT->lchild);
        printf("%c", BT->data);
        InOrderTraversal(BT->rchild);
    }
}
 
/*
 (3)后序遍历 递归解法
 遍历过程：
    1.遍历其左子树
    2.遍历其右子树
    3.访问根节点
*/
void PostOrderTraversal(BinaryTree* BT) {
    if (BT) {
        PostOrderTraversal(BT->lchild);
        PostOrderTraversal(BT->rchild);
        printf("%c", BT->data);
    }
}
 
int main(int argc, const char * argv[]) {
    BinaryTree* tree_A = CreateBinaryTree('A');
    
    BinaryTree* tree_B = CreateBinaryTree('B');
    tree_A->lchild = tree_B;
    
    BinaryTree* tree_C = CreateBinaryTree('C');
    tree_A->rchild = tree_C;
    
    BinaryTree* tree_D = CreateBinaryTree('D');
    tree_B->lchild = tree_D;
    
    BinaryTree* tree_F = CreateBinaryTree('F');
    tree_B->rchild = tree_F;
    
    BinaryTree* tree_E = CreateBinaryTree('E');
    tree_F->lchild = tree_E;
    
    BinaryTree* tree_G = CreateBinaryTree('G');
    tree_C->lchild = tree_G;
    
    BinaryTree* tree_I = CreateBinaryTree('I');
    tree_C->rchild = tree_I;
    
    BinaryTree* tree_H = CreateBinaryTree('H');
    tree_G->rchild = tree_H;
    
    //先序遍历 => A B D F E C G H I
    PreOrderTraversal(tree_A);
    
    printf("\n");
    
    //中序遍历 => D B E F A G H C I
    InOrderTraversal(tree_A);
    
    printf("\n");
    
    //后序遍历 => D E F B H G I C A
    PostOrderTraversal(tree_A);
    
    return 0;
}
