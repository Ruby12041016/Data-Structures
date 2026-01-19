#include <stdio.h>
#include <stdlib.h>

#define InitSize 10

typedef struct {
    int* data;     // 存储数据的数组
    int top;       // 栈顶指针
    int length;  // 当前容量
} ArrayStack;

//初始化
ArrayStack* createStack(){
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    stack->top = -1;
    stack->length = InitSize;
    stack->data = (int*)malloc(InitSize * sizeof(int));
    return stack;
}

//判空
int isEmpty(ArrayStack* stack){
    if(stack->top==-1){
        return 1;
    }
    return 0;
}

//判满
int isFull(ArrayStack* stack){
    if(stack->top+1==stack->length){
        return 1;
    }
    return 0;
}

//扩容
void resize(ArrayStack* stack){
    int newlength = 2 * stack->length;
    int* newdata = (int*)realloc(stack->data, newlength * sizeof(int));
    if(newdata==NULL){
        return;
    }
    stack->data = newdata;
    stack->length = newlength;
    printf("扩容至： %d\n", newlength);
    //free(newdata);
}

// 入栈
void push(ArrayStack* stack, int num){
    if (isFull(stack)) {
        resize(stack);
    }
    stack->data[++stack->top] = num;
}

//出栈
int pop(ArrayStack* stack){
    if (isEmpty(stack)) {
        printf("栈空\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// 获取栈大小
int size(ArrayStack* stack) {
    return stack->top + 1;
}

// 打印栈（从顶到底）
void printStack(ArrayStack* stack) {
    if (isEmpty(stack)) {
        printf("栈空\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

// 销毁栈
void destroyStack(ArrayStack* stack) {
    free(stack->data);
    free(stack);
}

int main() {
    ArrayStack* s = createStack();

    // 入栈，自动扩容
    for (int i = 1; i <= 15; i++) {
        push(s, i * 10);
    }
    printf("当前栈: ");
    printStack(s);

    // 出栈和栈空
    for (int i = 0; i < 15; i++) {
        printf("出栈: %d\n", pop(s));
        printf("当前栈: ");
        printStack(s);
    }
    
    //销毁
    destroyStack(s);
    return 0;
}
