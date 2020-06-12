/*
 ������������Binary Search Tree��Ҳ�ƶ������������߶��������
 1.�ǿ������������м�ֵС������ڵ�ļ�ֵ
 2.�ǿ������������м�ֵ��������ڵ�ļ�ֵ
 3.�����������Ƕ���������
 */
 
#include <stdio.h>
#include <stdlib.h>
 
#define ElementType int

typedef struct Node {
    ElementType data;
    struct Node *leftSubTree; //������
    struct Node *rightSubTree; //������
}BinaryTree;
 
//�����������ڵ�
BinaryTree* CreateBinaryTree(data) {
    BinaryTree* t = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (!t) {
        printf("�ռ䲻�㣡\n");
        return NULL;
    }
    t->leftSubTree = NULL;
    t->rightSubTree = NULL;
    t->data = data;
    return t;
}
 
/*
 �ݹ��㷨ʵ��
 ���ҴӸ��ڵ㿪ʼ�������Ϊ�գ����� NULL
 ���������ǿգ�����ڵ��ֵ��X���бȽϣ������в�ͬ����
 1.��XС�ڸ��ڵ��ֵ��ֻ�����������м�������
 2.��X���ڸ��ڵ��ֵ��ֻ�����������м�������
 */
BinaryTree* Find(ElementType x, BinaryTree* BST) {
    if (!BST) //���ҴӸ��ڵ㿪ʼ�������Ϊ�գ����� NULL
        return NULL;
    if (x > BST->data) //��X���ڸ��ڵ��ֵ��ֻ�����������м�������
        return Find(x, BST->rightSubTree);
    else if (x < BST->data) //��XС�ڸ��ڵ��ֵ��ֻ�����������м�������
        return Find(x, BST->leftSubTree);
    else
        return BST; //�����ȣ��������
}
 
//�ݹ��㷨�������Ԫ�� ���Ԫ��һ�����������ҷ�֦�Ľڵ���
BinaryTree* FindMax(BinaryTree* BST) {
    if (!BST)
        return NULL;
    else if (!BST->rightSubTree)
        return BST;
    else
        return FindMax(BST->rightSubTree);
}
//�ݹ��㷨������СԪ�� ��СԪ��һ������������߷�֦�Ľڵ���
BinaryTree* FindMin(BinaryTree* BST) {
    if (!BST)
        return NULL;
    else if (!BST->leftSubTree)
        return BST;
    else
        return FindMin(BST->leftSubTree);
}
 
//���ڷǵݹ麯����ִ��Ч�ʸߣ��ɽ��ݹ麯����Ϊ��������
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
 
//�����㷨�������Ԫ��
BinaryTree* FindMaxIteration(BinaryTree* BST) {
    if (BST)
        while (BST->rightSubTree) BST = BST->rightSubTree;
    return BST;
}
 
//�����㷨������СԪ��
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
    
    //�ݹ��㷨 ����Ԫ��x
    BinaryTree* searchTree = Find(7, tree_18);
    if (searchTree)
        printf("find = %d", searchTree->data);
    
    //�ݹ��㷨 �������Ԫ��
    BinaryTree* findMax = FindMax(tree_18);
    if (findMax)
        printf("\nfindMax = %d", findMax->data);
    
    //�ݹ��㷨 ������СԪ��
    BinaryTree* findMin = FindMin(tree_18);
    if (findMin)
        printf("\nfindMin = %d", findMin->data);
    
    
    //�����㷨 ����Ԫ��x
    BinaryTree* searchTreeIteration = FindIteration(20, tree_18);
    if (searchTreeIteration)
        printf("\nfind = %d", searchTreeIteration->data);
    
    //�����㷨 �������Ԫ��
    BinaryTree* findMaxIteration = FindMaxIteration(tree_18);
    if (findMaxIteration)
        printf("\nfindMax = %d", findMaxIteration->data);
    
    //�����㷨 ������СԪ��
    BinaryTree* findMinIteration = FindMinIteration(tree_18);
    if (findMin)
        printf("\nfindMin = %d", findMinIteration->data);
    
    return 0;
}
