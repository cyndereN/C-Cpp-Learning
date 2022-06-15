// T为非空串，若主串S中第pos个字符之后存在与T相等的子串，则返回第一个这样的字串在S中的位置，否则返回0

int Index(String S, String T, int pos){
    int n, m, i;
    String sub;
    if(pos>0) {
        n = StrLength(S);
        m = StrLength(T);
        i = pos;
        while (i<=n-m+1){
            SubString(sub, S, i, m); // 取第i个位置长度与T相等子串给sub
            if(StrCompare(sub, T)!=0) // 如果不相等
                ++i;
            else
                return i;
        }
    }
    return 0;
}

// 基本数组实现 最坏情况：O((n-m+1)*n)
int Index(String S, String T, int pos){
    int i = pos; // 主串S中当前位置下标
    int j = 1; // T中当前位置下标

    while(i<=S[0] && j<=T[0]){ // 假设S和T的长度存放在S[0]和T[0]
        if(S[i] == T[j]){
            ++i;
            ++j;
        } else {
            i = i-j+2; // 返回上一次匹配首位的下一位
            j = 1;
        }
    }
    if(j>T[0])
        return i-T[0];
    else
        return 0;

}