typedef int SElemType;
typedef struct {
    SElemType data[MAXSIZE];
    int top;
}SqStack;

Status Push(SqStack *S, SElemType e){
    if(S->top == MAXSIZE-1){ //栈满
        return ERROR;
    }
    S->top++;
    S->data[S->top]=e;
    return OK;
}

Status Pop(SqStack *S, SElemType *e){
    if(S->top==-1){
        return ERROR;
    }
    *e = S->data[S->top];
    S->top--;
    return OK;
}

//两栈共享空间结构
typedef struct {
    SElemType data[MAXSIZE]；
    int top1;
    int top2;
}SqDoubleStack;

Status Push(SqDoubleStack *S, SElemType e, int stackNumber){
    if(S->top+1==S->top2){
        //栈已满
        return ERROR;
    }
    if(stackNumber==1){
        S->data[++S->top1]=e;
    }else if(stackNumber==2){
        S->data{--S->top2}=e;
    }
}

Status Pop(SqDOubleStack *S, SElemType *e, int stackNumber){
    //若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK
    if(stackNumber==1){
        if(S->top1==-1)  return ERROR;
        *e = S->data[S->top1--]; 
    } else if (stackNumber==2){
        if(S->top2==MAXSIZE)    return ERROR;
        *e = S->data[S->top2++];
    }
    return OK;
}