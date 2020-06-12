#include <stdio.h>
#include <stdlib.h>
 
#define ElementType char

typedef struct Node {
    ElementType data;
    struct Node *lchild;
    struct Node *rchild;
}BinaryTree;
 
//�����������ڵ�
BinaryTree* CreateBinaryTree(data) {
    BinaryTree* t = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (!t) {
        printf("�ռ䲻�㣡\n");
        return NULL;
    }
    t->lchild = NULL;
    t->rchild = NULL;
    t->data = data;
    return t;
}
 
/*
 ��������нڵ����
 �ݹ�ⷨ��
 ��1�����������Ϊ�գ��ڵ����Ϊ0
 ��2�������������Ϊ�գ��������ڵ���� = �������ڵ���� + �������ڵ���� + 1
*/
int GetNodeNum(BinaryTree* BT) {
    if (BT == NULL)
        return 0;
    int leftNum = GetNodeNum(BT->lchild); //�������ڵ����
    int rightNum = GetNodeNum(BT->rchild); //�������ڵ����
    return (leftNum + rightNum + 1);
}
 
/*
 �������Ҷ�ӽڵ����
 �ݹ�ⷨ��
 ��1�����������Ϊ�գ�����0
 ��2�������������Ϊ������������Ϊ�գ�����1
 ��3�������������Ϊ�գ�������������ͬʱΪ�գ�������������Ҷ�ӽڵ����������������Ҷ�ӽڵ����
*/
int GetLeafNodeNum(BinaryTree* BT) {
    if (BT == NULL)
        return 0;
    if (BT->lchild == NULL && BT->rchild == NULL)
        return 1;
    int leftNum = GetLeafNodeNum(BT->lchild); //��������Ҷ�ӽڵ����
    int rightNum = GetLeafNodeNum(BT->rchild); //��������Ҷ�ӽڵ����
    return (leftNum + rightNum);
}
 
/*
 ������������
 �ݹ�ⷨ��
 ��1�����������Ϊ�գ������������Ϊ0
 ��2�������������Ϊ�գ������������ = max(��������ȣ� ���������) + 1
*/
int GetDepth(BinaryTree* BT) {
    if (BT == NULL)
        return 0;
    int leftDepth = GetDepth(BT->lchild); //���������
    int rightDepth = GetDepth(BT->rchild); //���������
    int maxDepth = (leftDepth > rightDepth) ? leftDepth : rightDepth;
    return (maxDepth + 1);
}
 
/*
 ���������K��Ľڵ����
 �ݹ�ⷨ��
 ��1�����������Ϊ�ջ���k<1����0
 ��2�������������Ϊ�ղ���k==1������1
 ��3�������������Ϊ����k>1��������������k-1��Ľڵ������������k-1��ڵ����֮��
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
    printf("�������ڵ������%d", num);
    
    int depth = GetDepth(tree_A);
    printf("\n��������ȣ�%d", depth);
    
    int k = 3;
    int kthNum  = GetNodeNumKthLevel(tree_A, k);
    printf("\n��������%d��ڵ�����%d", k, kthNum);
    
    int leafNum = GetLeafNodeNum(tree_A);
    printf("\n������Ҷ�ӽڵ������%d", leafNum);
    
    return 0;
}
