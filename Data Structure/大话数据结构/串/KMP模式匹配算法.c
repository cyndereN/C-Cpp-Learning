// next[]数组根据前缀后缀确定j值的回溯位置
// 前后缀部分匹配
void get_next(String T, int* next){
    int i,j;
    i = 1;
    j = 0;
    next[1] = 0;
    while(i<T[0]){ // T[0]表示串T长度  
        if(j==0 || T[i]==T[j]){
            ++i;++j;
            next[i] = j;
        } else {
            j = next[j];  // 若字符不相同，则j值回溯
        }
    }
}
// O(n+m)
int Index_KMP(String S, String T, int pos){
    int i = pos; // 主串S中当前位置下标
    int j = 1; // T中当前位置下标

    int next[255];
    get_next(T, next);

    while(j==0 || i<=S[0] && j<=T[0]){ // 假设S和T的长度存放在S[0]和T[0]
        if(S[i] == T[j]){
            ++i;
            ++j;
        } else {
            j = next[j];  // j退回合适位置，i不变
        }
    }
    if(j>T[0])
        return i-T[0];
    else
        return 0;

}


// 改进
// 前缀重复相同字符匹配
void get_nextval(String T, int* nextval){
    int i,j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while(i<T[0]){ // T[0]表示串T长度  
        if(j==0 || T[i]==T[j]){
            ++i;++j;
            if(T[i]!=T[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j]; // 如果前缀字符相同 则把前缀字符的nextval值赋值给nextval在i位置的值
        } else {
            j = next[j];  // 若字符不相同，则j值回溯
        }
    }
}