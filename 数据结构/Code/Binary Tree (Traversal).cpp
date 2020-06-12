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
 (1)������� �ݹ�ⷨ
 ��������Ϊ��
    1.���ʸ��ڵ�
    2.������������
    3.������������
*/
void PreOrderTraversal(BinaryTree* BT) {
    if (BT) {
        printf("%c", BT->data);
        PreOrderTraversal(BT->lchild);
        PreOrderTraversal(BT->rchild);
    }
}
 
/*
 (2)������� �ݹ�ⷨ
 �������̣�
    1.������������
    2.���ʸ��ڵ�
    3.������������
*/
void InOrderTraversal(BinaryTree* BT) {
    if (BT) {
        InOrderTraversal(BT->lchild);
        printf("%c", BT->data);
        InOrderTraversal(BT->rchild);
    }
}
 
/*
 (3)������� �ݹ�ⷨ
 �������̣�
    1.������������
    2.������������
    3.���ʸ��ڵ�
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
    
    //������� => A B D F E C G H I
    PreOrderTraversal(tree_A);
    
    printf("\n");
    
    //������� => D B E F A G H C I
    InOrderTraversal(tree_A);
    
    printf("\n");
    
    //������� => D E F B H G I C A
    PostOrderTraversal(tree_A);
    
    return 0;
}
