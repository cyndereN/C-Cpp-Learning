// 有序表在插入和删除上耗费大量时间

// 二叉排序树：

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/*递归查找二叉排序树T中是否存在key，指针f指向T的双亲，起始调用值为NULL
若查找成功，则指针p指向该数据元素结点，并返回TRUE
否则指针p指向查找路径上访问的最后一个结点并返回FALSE。*/

Status SearchBST(BiTree T, int key, BiTree f, BiTree *p){
    if (!T){
        *p = f;
        return FALSE;
    } else if (key == T->data){
        *p = T;
        return TRUE;
    } else if (key < T->data){
        return SearchBST(T->lchild, key, T, p);
    } else {
        return SearchBST(T->rchild, key, T, p);
    }
}


Status InsertBST(BiTree *T, int key) {
    BiTree p,s;

    if(!SearchBST(*T, key, NULL, &p)){
        s = (BiTree) malloc (sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;

        if(!p)
            *T = s;   // 插入s为新的根节点
        else if (key < p->data)
            p->lchild = s;
        else
            p->rchild = s;
        return TRUE;
        
    }

    return FALSE;  // 已有关键字相同的结点不再插入
}

// 删除：用左子树最右子节点或右子树最左子节点替换，再重截子树