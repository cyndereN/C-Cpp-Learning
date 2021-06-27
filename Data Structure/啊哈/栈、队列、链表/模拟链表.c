/*新建数组以储存序列中每一个元素右边的元素在数组中的位置*/
#include <stdio.h>
int main(){
    int data[101], right[101];
    int i, n, t, len;
    scanf("%d",&n);

    for(i=0; i<=n; i++){
        scanf("%d", &data[i]);
    }
    len = n;
    for(i=0; i<=n; i++){
        if(i!=n)  right[i] = i+1;
        else  right[i] = 0;
    }
    // 直接在data末尾添加
    len++;
    scanf("%d", &data[len]);
    //从头部开始遍历
    t = 1;
    while(t!=0){
        if(data[right[t]]>data[len]){
            // 如果当前节点下一个节点的值大于待插入数，将数插入中间
            right[len] = right[t];
            right[t] = len;
            break;
        }
        t = right[t];
    }
    // 输出链表中所有数
    t = 1;
    while(t!=0){
        printf("%d ", data[t]);
        t = right[t];
    }
    return 0;
}