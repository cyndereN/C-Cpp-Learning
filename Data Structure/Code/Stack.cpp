#include <stdio.h>
#include <stdlib.h>
 
#define ElementType int //存储数据元素的类型
#define MAXSIZE 1024 //存储数据元素的最大个数
#define ERROR -99 //ElementType的特殊值，标志错误
 
//堆栈的顺序存储结构通常由一个一维数组和一个记录栈顶元素位置的变量组成
typedef struct {
    ElementType data[MAXSIZE];
    int top;
}Stack;
 
//初始化栈
Stack* InitStack() {
    Stack* stack;
    stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        printf("空间不足\n");
        return NULL;
    }
    stack->top = -1;
    return stack;
}
 
int IsFull(Stack* stack) {
    if (stack->top == MAXSIZE - 1) {
        printf("堆栈已满\n");
        return 1;
    }
    return 0;
}
 
int IsEmpty(Stack* stack) {
    if (stack->top == -1) {
        printf("堆栈空\n");
        return 1;
    }
    return 0;
}
 
//入栈
void Push(Stack* stack, ElementType item) {
    if (IsFull(stack)) {
        return;
    }
    stack->data[++stack->top] = item;
}
 
//出栈
ElementType Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        return ERROR;
    }
    return stack->data[stack->top--];
}
 
void PrintStack(Stack* stack) {
    printf("当前栈中的元素:\n");
    int i;
    for (i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

void DestroyStack(Stack* stack){
	free(stack);
}
 
int main(int argc, const char * argv[]) {
    Stack* stack;
    stack = InitStack();
 
    Push(stack, 1);
    Push(stack, 2);
    Push(stack, 3);
    Push(stack, 4);
    Push(stack, 5);
    
    PrintStack(stack);
    
    Pop(stack);
    Pop(stack);
    
    PrintStack(stack);
    
    DestroyStack(stack);
    
    return 0;
}
