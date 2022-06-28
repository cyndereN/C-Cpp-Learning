// AVL 一种二叉排序树，每一个节点的左子树和右子树的高度差至多等于1

// BF 二叉树上节点的左子树减去右子树深度的值称为平衡因子

typedef struct BiTNode{
    int data;
    int bf;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
// int *p ; 指向一个整型的指针。
// 如果，在前面我们使用了 typedef int * Pint;
// 则上面的声明方法，可以改为： Pint p;同样是声明一个指向整型的指针。

void R_Rotate(BiTree *P) { // 左子树顺时针旋转
    BiTree L;
    L = (*P) -> lchild;
    (*P)->lchild = L->lchild;
    L->rchild = (*P);
    *P = L;
}
