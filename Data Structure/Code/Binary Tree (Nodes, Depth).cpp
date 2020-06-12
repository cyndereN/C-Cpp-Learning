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
 求二叉树中节点个数
 递归解法：
 （1）如果二叉树为空，节点个数为0
 （2）如果二叉树不为空，二叉树节点个数 = 左子树节点个数 + 右子树节点个数 + 1
*/
int GetNodeNum(BinaryTree* BT) {
    if (BT == NULL)
        return 0;
    int leftNum = GetNodeNum(BT->lchild); //左子树节点个数
    int rightNum = GetNodeNum(BT->rchild); //右子树节点个数
    return (leftNum + rightNum + 1);
}
 
/*
 求二叉树叶子节点个数
 递归解法：
 （1）如果二叉树为空，返回0
 （2）如果二叉树不为空且左右子树为空，返回1
 （3）如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数
*/
int GetLeafNodeNum(BinaryTree* BT) {
    if (BT == NULL)
        return 0;
    if (BT->lchild == NULL && BT->rchild == NULL)
        return 1;
    int leftNum = GetLeafNodeNum(BT->lchild); //左子树中叶子节点个数
    int rightNum = GetLeafNodeNum(BT->rchild); //右子树中叶子节点个数
    return (leftNum + rightNum);
}
 
/*
 求二叉树的深度
 递归解法：
 （1）如果二叉树为空，二叉树的深度为0
 （2）如果二叉树不为空，二叉树的深度 = max(左子树深度， 右子树深度) + 1
*/
int GetDepth(BinaryTree* BT) {
    if (BT == NULL)
        return 0;
    int leftDepth = GetDepth(BT->lchild); //左子树深度
    int rightDepth = GetDepth(BT->rchild); //右子树深度
    int maxDepth = (leftDepth > rightDepth) ? leftDepth : rightDepth;
    return (maxDepth + 1);
}
 
/*
 求二叉树第K层的节点个数
 递归解法：
 （1）如果二叉树为空或者k<1返回0
 （2）如果二叉树不为空并且k==1，返回1
 （3）如果二叉树不为空且k>1，返回左子树中k-1层的节点个数与右子树k-1层节点个数之和
*/
int GetNodeNumKthLevel(BinaryTree* BT, int k) {
    if (BT == NULL || k < 1)
        return 0;
    if (k == 1)
        return 1;
    int leftNum = GetNodeNumKthLevel(BT->lchild, k - 1);
    int rightNum = GetNodeNumKthLevel(BT->rchild, k - 1);
    return (leftNum + rightNum);
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
    
    int num = GetNodeNum(tree_A);
    printf("二叉树节点个数：%d", num);
    
    int depth = GetDepth(tree_A);
    printf("\n二叉树深度：%d", depth);
    
    int k = 3;
    int kthNum  = GetNodeNumKthLevel(tree_A, k);
    printf("\n二叉树第%d层节点数：%d", k, kthNum);
    
    int leafNum = GetLeafNodeNum(tree_A);
    printf("\n二叉树叶子节点个数：%d", leafNum);
    
    return 0;
}
