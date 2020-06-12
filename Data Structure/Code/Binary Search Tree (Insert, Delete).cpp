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
 
//�����������Ĳ���
BinaryTree* Insert(ElementType x, BinaryTree* BST) {
    if (!BST) {
        //��ԭ��Ϊ�գ����ɲ�����һ���ڵ�Ķ���������
        BST = CreateBinaryTree(x);
        BST->leftSubTree = NULL;
        BST->rightSubTree = NULL;
    }
    else { //��ʼ��Ҫ����Ԫ�ص�λ��
        if (x > BST->data)
            BST->rightSubTree = Insert(x, BST->rightSubTree); //�ݹ����������
        else if (x < BST->data)
            BST->leftSubTree = Insert(x, BST->leftSubTree); //�ݹ����������
    }
    return BST;
}
 
//������������ɾ��
BinaryTree* Delete(ElementType x, BinaryTree* BST) {
    BinaryTree* Temp;
    if (!BST)
        printf("\nδ�ҵ�Ҫɾ����Ԫ��%d", x);
    else if (x < BST->data)
        BST->leftSubTree = Delete(x, BST->leftSubTree); //�������ݹ�ɾ��
    else if (x > BST->data)
        BST->rightSubTree = Delete(x, BST->rightSubTree); //�������ݹ�ɾ��
    else { //�ҵ�Ҫɾ���Ľڵ�
        if (BST->leftSubTree && BST->rightSubTree) { //��ɾ���ڵ������������ӽڵ�
            Temp = FindMin(BST->rightSubTree); //��������������СԪ�����ɾ���ڵ�
            BST->data = Temp->data;
            BST->rightSubTree = Delete(BST->data, BST->rightSubTree); //��ɾ���ڵ����������ɾ����СԪ��
        }
        else { //��ɾ���ڵ���һ�������ӽڵ�
            Temp = BST;
            if (!BST->leftSubTree) //���Һ��ӻ����ӽڵ�
                BST = BST->rightSubTree;
            else if (!BST->rightSubTree) //�����ӻ����ӽڵ�
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
    if (findBT1) printf("find1��%d", findBT1->data);
    
    BinaryTree* findBT2 = Find(22, root);
    if (findBT2) printf("\nfind2��%d", findBT2->data);
    
    Delete(10, root);
    BinaryTree* findBT3 = Find(10, root);
    if (findBT3) printf("\nfind3��%d", findBT3->data);
    
    BinaryTree* findBT4 = Find(9, root);
    if (findBT4) printf("\nfind4��%d", findBT4->data);
    
    Delete(9, root);
    BinaryTree* findBT5 = Find(9, root);
    if (findBT5) printf("\find5��%d", findBT5->data);
    
    return 0;
}
