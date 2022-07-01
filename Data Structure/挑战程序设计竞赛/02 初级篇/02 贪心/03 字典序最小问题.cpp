// 给定长度为N字符串S，构造一个长度为N的字符串T。起初T是个空串，随后反复进行下列任意操作：
// · 从S的头部删除一个字符，加到T的尾部
// · 从S的尾部删除一个字符，加到T的头部
// 目标是构造字典序尽可能小的字符串T

// 解法：不断取S的开头和末尾中较小的一个字符放到T的末尾


// 输入
int N;
char S[MAX_N+1];

void solve(){
    // 剩余字符串为S[a], S[a+1], ... S[b]

    // 相当于指向头尾的指针
    int a = 0, b = N-1;

    while (a<=b){
        // 将从左起和从右起的字符串比较
        bool left = false;

        for(int i =0; a+i <=b; i++) {
            if (S[a+i] < S[b-i]){
                left = true;
                break;
            }
            else if (S[a+i] > S[b-i]) {
                left = false;
                break;
            }
        }
        if (left)  putchar(S[a++]);
        else putchar(S[b--]);
    }
    putchar('\n');
}