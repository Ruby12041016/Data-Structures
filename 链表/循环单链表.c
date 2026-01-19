#include <stdio.h>
#include <stdlib.h>

typedef struct CNode {
    int data;
    struct CNode* next;
} CNode;  

// 初始化循环单链表（
void InitList(CNode** L) {
    *L = (CNode*)malloc(sizeof(CNode));
    if (*L == NULL)
        return;     
    (*L)->next = *L;  
}

//头插法建立
void CreateList_Head(CNode* l, int arr[], int n){
    for (int i = 0; i < n;i++){
        CNode* new = (CNode*)malloc(sizeof(CNode));
        new->data = arr[i];
        new->next = l->next;
        l->next = new;
    }
}

//尾插法建立
void CreateList_Tail(CNode* l, int arr[], int n){
    CNode* tail = l;
    for (int i = 0; i < n; i++) {
        CNode* new = (CNode*)malloc(sizeof(CNode));
        new->data = arr[i];
        new->next = l;
        tail->next = new;
        tail = new;
    }
}

//判空
int IsEmpty(CNode* L) {
    if (L->next == L){
        return 1;
    }
    return 0;
}

//按值查找
CNode* LocateElem(CNode* L, int num){
    CNode* p = L->next; 
    while (p != L) {
        if (p->data == num)
            return p;
        p = p->next;
    }
    return NULL;
}

//按位查找
CNode* GetElem(CNode* L, int i){
    if(i<1){
        return NULL;
    }
    int j = 0;
    CNode* p = L;
    while(j<i&&p->next!=L){
        p = p->next;
        j++;
    }
    if(j==i){
        return p;
    }
    return NULL;
}

//在第i个位置插入元素
int ListInsert(CNode* L, int i, int num){
    if (i < 1) {
        return 0;
    }
   // CNode* p = L;
    //int j = 0;
    CNode* new = (CNode*)malloc(sizeof(CNode));
    new->data = num;
    // while (j < i-1 && p->next != L) {
    //     p = p->next;
    //     j++;
    // }
    // if(j==i-1){
    CNode* p = GetElem(L, i - 1);
    new->next = p->next;
    p->next = new;
    return 1;
    // }
    return 0;
}

// 删除第 i 个节点
int ListDelete(CNode* L, int i){
    if (i < 1) {
        return 0;
    }
    CNode* p = GetElem(L, i - 1);
    if (p == NULL || p->next == L){
        return 0;
    }
    CNode* q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}

//打印
void PrintList(CNode* L){
    if (IsEmpty(L)) {
        printf("空表\n");
        return;
    }
    CNode* p = L->next;
    while (p != L) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//销毁
void DestroyList(CNode* L) {
    CNode* p = L->next;  
    while (p != L) {    
        CNode* now = p;
        p = p->next;
        free(now);
    }
    free(L);  
}

int main() {
    CNode* L;
    InitList(&L);
    CNode* L1;
    InitList(&L1);
    int arr[] = {1, 2, 3, 4, 5};

    //头插法
    CreateList_Head(L, arr, 5);
    printf("头插法建立的：\n");
    PrintList(L);

    //尾插法
    CreateList_Tail(L1, arr, 4);
    printf("尾插法建立的：\n");
    PrintList(L1);

    // 在位置3插入6
    ListInsert(L, 3, 6);
    printf("在位置3插入6后：\n");
    PrintList(L);

    // 删除第四个元素
    ListDelete(L, 4);
    printf("删除第四个元素后:\n");
    PrintList(L);

    // 查找元素n
    int n;
    printf("输入要找的元素：\n");
    scanf("%d", &n);
    CNode* i = LocateElem(L, n);
    if (i != NULL){
        printf("找到元素%d\n",n);
    }else{
        printf("未找到元素%d\n", n);
    }

    DestroyList(L);
    DestroyList(L1);
    return 0;
}