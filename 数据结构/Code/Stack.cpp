#include <stdio.h>
#include <stdlib.h>
 
#define ElementType int //�洢����Ԫ�ص�����
#define MAXSIZE 1024 //�洢����Ԫ�ص�������
#define ERROR -99 //ElementType������ֵ����־����
 
//��ջ��˳��洢�ṹͨ����һ��һά�����һ����¼ջ��Ԫ��λ�õı������
typedef struct {
    ElementType data[MAXSIZE];
    int top;
}Stack;
 
//��ʼ��ջ
Stack* InitStack() {
    Stack* stack;
    stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        printf("�ռ䲻��\n");
        return NULL;
    }
    stack->top = -1;
    return stack;
}
 
int IsFull(Stack* stack) {
    if (stack->top == MAXSIZE - 1) {
        printf("��ջ����\n");
        return 1;
    }
    return 0;
}
 
int IsEmpty(Stack* stack) {
    if (stack->top == -1) {
        printf("��ջ��\n");
        return 1;
    }
    return 0;
}
 
//��ջ
void Push(Stack* stack, ElementType item) {
    if (IsFull(stack)) {
        return;
    }
    stack->data[++stack->top] = item;
}
 
//��ջ
ElementType Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        return ERROR;
    }
    return stack->data[stack->top--];
}
 
void PrintStack(Stack* stack) {
    printf("��ǰջ�е�Ԫ��:\n");
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
