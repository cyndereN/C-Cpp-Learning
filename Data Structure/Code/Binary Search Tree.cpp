/*
 二叉搜索树（Binary Search Tree）也称二叉排序树或者二叉查找树
 1.非空左子树的所有键值小于其根节点的键值
 2.非空右子树的所有键值大于其根节点的键值
 3.左右子树都是二叉搜索树
 */
 
#include <stdio.h>
#include <stdlib.h>
 
#define ElementType int

typedef struct Node {
    ElementType data;
    struct Node *leftSubTree; //左子树
    struct Node *rightSubTree; //右子树
}BinaryTree;
 
//创建二叉树节点
BinaryTree* CreateBinaryTree(data) {
    BinaryTree* t = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (!t) {
        printf("空间不足！\n");
        return NULL;
    }
    t->leftSubTree = NULL;
    t->rightSubTree = NULL;
    t->data = data;
    return t;
}
 
/*
 递归算法实现
 查找从根节点开始，如果树为空，返回 NULL
 若搜索树非空，则根节点键值和X进行比较，并进行不同处理
 1.若X小于根节点键值，只需在左子树中继续搜索
 2.若X大于根节点键值，只需在右子树中继续搜索
 */
BinaryTree* Find(ElementType x, BinaryTree* BST) {
    if (!BST) //查找从根节点开始，如果树为空，返回 NULL
        return NULL;
    if (x > BST->data) //若X大于根节点键值，只需在右子树中继续搜索
        return Find(x, BST->rightSubTree);
    else if (x < BST->data) //若X小于根节点键值，只需在左子树中继续搜索
        return Find(x, BST->leftSubTree);
    else
        return BST; //结果相等，搜索完成
}
 
//递归算法查找最大元素 最大元素一定在树的最右分枝的节点上
BinaryTree* FindMax(BinaryTree* BST) {
    if (!BST)
        return NULL;
    else if (!BST->rightSubTree)
        return BST;
    else
        return FindMax(BST->rightSubTree);
}
//递归算法查找最小元素 最小元素一定在树的最左边分枝的节点上
BinaryTree* FindMin(BinaryTree* BST) {
    if (!BST)
        return NULL;
    else if (!BST->leftSubTree)
        return BST;
    else
        return FindMin(BST->leftSubTree);
}
 
//由于非递归函数的执行效率高，可将递归函数改为迭代函数
BinaryTree* FindIteration(ElementType x, BinaryTree* BST) {
    while (BST) {
        if (x > BST->data)
            BST = BST->rightSubTree;
        else if (x < BST->data)
            BST = BST->leftSubTree;
        else
            return BST;
    }
    return NULL;
}
 
//迭代算法查找最大元素
BinaryTree* FindMaxIteration(BinaryTree* BST) {
    if (BST)
        while (BST->rightSubTree) BST = BST->rightSubTree;
    return BST;
}
 
//迭代算法查找最小元素
BinaryTree* FindMinIteration(BinaryTree* BST) {
    if (BST)
        while (BST->leftSubTree) BST = BST->leftSubTree;
    return BST;
}
 
int main(int argc, const char * argv[]) {
    BinaryTree* tree_18 = CreateBinaryTree(18);
    
    BinaryTree* tree_10 = CreateBinaryTree(10);
    tree_18->leftSubTree = tree_10;
    
    BinaryTree* tree_20 = CreateBinaryTree(20);
    tree_18->rightSubTree = tree_20;
    
    BinaryTree* tree_7 = CreateBinaryTree(7);
    tree_10->leftSubTree = tree_7;
    
    BinaryTree* tree_15 = CreateBinaryTree(15);
    tree_10->rightSubTree = tree_15;
    
    BinaryTree* tree_9 = CreateBinaryTree(9);
    tree_7->rightSubTree = tree_9;
    
    BinaryTree* tree_22 = CreateBinaryTree(22);
    tree_20->rightSubTree = tree_22;
    
    //递归算法 查找元素x
    BinaryTree* searchTree = Find(7, tree_18);
    if (searchTree)
        printf("find = %d", searchTree->data);
    
    //递归算法 查找最大元素
    BinaryTree* findMax = FindMax(tree_18);
    if (findMax)
        printf("\nfindMax = %d", findMax->data);
    
    //递归算法 查找最小元素
    BinaryTree* findMin = FindMin(tree_18);
    if (findMin)
        printf("\nfindMin = %d", findMin->data);
    
    
    //迭代算法 查找元素x
    BinaryTree* searchTreeIteration = FindIteration(20, tree_18);
    if (searchTreeIteration)
        printf("\nfind = %d", searchTreeIteration->data);
    
    //迭代算法 查找最大元素
    BinaryTree* findMaxIteration = FindMaxIteration(tree_18);
    if (findMaxIteration)
        printf("\nfindMax = %d", findMaxIteration->data);
    
    //迭代算法 查找最小元素
    BinaryTree* findMinIteration = FindMinIteration(tree_18);
    if (findMin)
        printf("\nfindMin = %d", findMinIteration->data);
    
    return 0;
}
