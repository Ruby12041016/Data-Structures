#include <stdio.h>
#include <stdlib.h>

// 链表栈节点
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// 链表栈
typedef struct {
    StackNode* top;
    int size;
} LinkedStack;

// 初始化
LinkedStack* createLinkedStack(){
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

// 创建新节点
StackNode* createNode(int num){
    StackNode* new = (StackNode*)malloc(sizeof(StackNode));
    new->data = num;
    new->next = NULL;
    return new;
}

// 入栈
void lpush(LinkedStack* stack, int num){
    StackNode* new = createNode(num);
    new->next = stack->top;
    stack->top = new;
    stack->size++;
}

//判空
int lisEmpty(LinkedStack* stack){
    if(stack->top==NULL){
        return 1;
    }
    return 0;
}

// 出栈
int lpop(LinkedStack* stack) {
    if (lisEmpty(stack)){
        printf("栈空\n");
        return -1;
    }
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    int num=temp->data;
    free(temp);
    stack->size--;
    return num;
}

// 获取链表栈大小
int lsize(LinkedStack* stack) {
    return stack->size;
}

// 打印
void lprintStack(LinkedStack* stack) {
    if (lisEmpty(stack)) {
        printf("栈空\n");
        return;
    }
    StackNode* p = stack->top;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 销毁
void ldestroyStack(LinkedStack* stack) {
    while (stack->top != NULL) {
        StackNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}

int main() {
    LinkedStack* s = createLinkedStack();

    for (int i = 1; i <= 5; i++){
        lpush(s, i * 10);
        printf("入栈后: ");
        lprintStack(s);
    }

    int size = lsize(s);
    printf("栈大小为：%d\n", size);

    for (int i = 0; i < 5; i++){
        printf("出栈: %d\n", lpop(s));
        printf("剩余栈: ");
        lprintStack(s);
    }
    ldestroyStack(s);
    return 0;
}
