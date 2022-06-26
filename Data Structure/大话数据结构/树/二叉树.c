// n (n>=0)个结点的有限集合，该集合或者未空集（称为空二叉树），或者由一个根节点和两
// 棵互不相交的、分别称为根节点的左子树和右子树的二叉树组成

// 性质：
// 第i层至多2^(i-1)个结点
// 深度为k的二叉树至多2^k-1个节点
// 任意一棵二叉树，终端节点数为n0, 度为2的节点n2，n0=n2+1

// 顺序存储结构一般用于完全二叉树，否则会造成空间浪费。一般用链表


// 遍历：
// 前序：根，左，右
void PreOrderTraverse(BiTree T){
    if (T==NULL){
        printf("%c", T->data);
    }

    PreOrderTraverse(T->lchild);

    PreOrderTraverse(T->rchild);
}
// 中序：左，根，右
// 后序：左，右，根
// 层序
// 扩展二叉树可以做到一个遍历序列确定一棵二叉树


// 建立：
void CreateBiTree(BiTree *T){
    TElemType ch;
    scanf("%c", &ch);

    if(ch=="#")
        *T = NULL;

    else{
        *T = (BiTree) malloc (sizeof(BiTNode));
        if(!*T) 
            exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

// 树转换为二叉树————加线，去线，层次调整。因为二叉树结构不那么复杂，比较方便研究性质算法
// 森林中的每棵树都是兄弟