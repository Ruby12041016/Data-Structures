#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 6

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} CircularQueue;

// 初始化
void InitQueue(CircularQueue* Q) {
    Q->front = 0;
    Q->rear = 0;
}

// 判空
int QueueEmpty(CircularQueue* Q) {
    if(Q->front == Q->rear){
        return 1;
    }
    return 0;
}

// 判满
int QueueFull(CircularQueue* Q) {
    if((Q->rear + 1) % MAXSIZE == Q->front){
        return 1;
    }
    return 0;
}

// 入队
void EnQueue(CircularQueue* Q, int num) {
    if (QueueFull(Q)) {
        printf("队列已满，无法入队！\n");
        return;
    }
    Q->data[Q->rear] = num;               
    Q->rear = (Q->rear + 1) % MAXSIZE;  
}

// 出队
int DeQueue(CircularQueue* Q) {
    if (QueueEmpty(Q)) {
        printf("队列为空，无法出队！\n");
        return -1;
    }

    int num = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;  
    return num;
}

// 获取队头元素
int GetHead(CircularQueue* Q) {
    if (QueueEmpty(Q)) {
        printf("队列为空！\n");
        return -1;
    }

    int num = Q->data[Q->front];
    return num;
}

// 获取队列长度
int QueueLength(CircularQueue* Q) {
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

// 遍历，打印队列
void TraverseQueue(CircularQueue* Q) {
    if (QueueEmpty(Q)) {
        printf("队列为空！\n");
        return;
    }
    printf("队列元素: ");
    int i = Q->front;
    while (i != Q->rear) {
        printf("%d ", Q->data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
}

int main() {
    CircularQueue Q;
    int num;

    //初始化
    InitQueue(&Q);

    // 入队和判满
    for (int i = 1; i <= 5; i++) {
        EnQueue(&Q, i * 10);
        printf("入队: %d\n", i * 10);
        TraverseQueue(&Q);
    }
   
    // 出队和判空
    for (int i = 1; i <= 5; i++) {
        num = DeQueue(&Q);
        printf("出队: %d\n", i * 10);
        TraverseQueue(&Q);
    }
    
    // 获取队头
    num = GetHead(&Q);
    printf("队头元素: %d\n", num);

    // 获取队列长度
    printf("队列长度: %d\n", QueueLength(&Q));
    return 0;
}