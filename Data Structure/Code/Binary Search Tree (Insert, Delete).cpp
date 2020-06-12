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
 
BinaryTree* Find(ElementType x, BinaryTree* BST) {
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
 
BinaryTree* FindMin(BinaryTree* BST) {
    if (BST)
        while (BST->leftSubTree) BST = BST->leftSubTree;
    return BST;
}
 
//二叉搜索树的插入
BinaryTree* Insert(ElementType x, BinaryTree* BST) {
    if (!BST) {
        //若原树为空，生成并返回一个节点的二叉搜索树
        BST = CreateBinaryTree(x);
        BST->leftSubTree = NULL;
        BST->rightSubTree = NULL;
    }
    else { //开始找要插入元素的位置
        if (x > BST->data)
            BST->rightSubTree = Insert(x, BST->rightSubTree); //递归插入右子树
        else if (x < BST->data)
            BST->leftSubTree = Insert(x, BST->leftSubTree); //递归插入左子树
    }
    return BST;
}
 
//二叉搜索树的删除
BinaryTree* Delete(ElementType x, BinaryTree* BST) {
    BinaryTree* Temp;
    if (!BST)
        printf("\n未找到要删除的元素%d", x);
    else if (x < BST->data)
        BST->leftSubTree = Delete(x, BST->leftSubTree); //左子树递归删除
    else if (x > BST->data)
        BST->rightSubTree = Delete(x, BST->rightSubTree); //右子树递归删除
    else { //找到要删除的节点
        if (BST->leftSubTree && BST->rightSubTree) { //被删除节点有左右两个子节点
            Temp = FindMin(BST->rightSubTree); //在右子树中找最小元素填充删除节点
            BST->data = Temp->data;
            BST->rightSubTree = Delete(BST->data, BST->rightSubTree); //在删除节点的右子树中删除最小元素
        }
        else { //被删除节点有一个或无子节点
            Temp = BST;
            if (!BST->leftSubTree) //有右孩子或无子节点
                BST = BST->rightSubTree;
            else if (!BST->rightSubTree) //有左孩子或无子节点
                BST = BST->leftSubTree;
            free(Temp);
        }
    }
    return BST;
}
 
int main(int argc, const char * argv[]) {
    BinaryTree* root = CreateBinaryTree(18);
    Insert(10, root);
    Insert(20, root);
    Insert(7, root);
    Insert(15, root);
    Insert(9, root);
    Insert(22, root);
    
    BinaryTree* findBT1 = Find(15, root);
    if (findBT1) printf("find1：%d", findBT1->data);
    
    BinaryTree* findBT2 = Find(22, root);
    if (findBT2) printf("\nfind2：%d", findBT2->data);
    
    Delete(10, root);
    BinaryTree* findBT3 = Find(10, root);
    if (findBT3) printf("\nfind3：%d", findBT3->data);
    
    BinaryTree* findBT4 = Find(9, root);
    if (findBT4) printf("\nfind4：%d", findBT4->data);
    
    Delete(9, root);
    BinaryTree* findBT5 = Find(9, root);
    if (findBT5) printf("\find5：%d", findBT5->data);
    
    return 0;
}
