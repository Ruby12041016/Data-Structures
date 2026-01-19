#include<stdio.h>
#include<stdlib.h>

typedef struct DNode {
    int data;             
    struct DNode* prior;  
    struct DNode* next;   
} CDNode;

// 初始化带头节点的循环双链表
CDNode* InitList() {
    CDNode* L = (CDNode*)malloc(sizeof(CDNode));  
    if (L == NULL) {
        return NULL;
    }
    L->prior = L; 
    L->next = L;   
    return L;
}

// 头插法创建链表
void CreateListHead(CDNode* L, int arr[], int n){
    for (int i = 0; i < n;i++){
        CDNode* new = (CDNode*)malloc(sizeof(CDNode));
        if (new == NULL) {
            return;
        }
        new->data = arr[i];
        new->next = L->next;
        new->prior = L;
        L->next->prior = new;
        L->next = new;
    }
}

// 位插法建立链表
void CreateListTail(CDNode* L, int arr[], int n){
    CDNode* p = L;
    for (int i = 0; i < n;i++){
        CDNode* new = (CDNode*)malloc(sizeof(CDNode));
        if (new == NULL) {
            return;
        }
        new->data = arr[i];
        new->next = L;
        new->prior = p;
        p->next = new;
        L->prior = new;
        p = new;
    }
}

// 判空
int IsEmpty(CDNode* L){
    if(L->next==L){
        return 1;
    }
    return 0;
}

// 正向遍历链表并打印
void PrintListForward(CDNode* L) {
    if(IsEmpty(L)){
        printf("链表为空\n");
        return;
    }
    CDNode* p = L->next;
    while (p != L) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 反向遍历链表并打印
void PrintListBackward(CDNode* L){
    if (IsEmpty(L)) {
        printf("链表为空\n");
        return;
    }
    CDNode* p = L->prior;
    while (p != L) {
        printf("%d ", p->data);
        p = p->prior;
    }
    printf("\n");
}

// // 按值查找(和单链表一样)
// CDNode* LocateElem(CDNode* L, int num){
//     CDNode* p = L->next;
//     while (p != L) {
//         if (p->data == num)
//             return p;
//         p = p->next;
//     }
//     return NULL;
// }

// 按位查找(和单链表一样)
CDNode* GetElem(CDNode* L, int i) {
    if (i < 1) {
        return NULL;
    }
    int j = 0;
    CDNode* p = L;
    while (j < i && p->next != L) {
        p = p->next;
        j++;
    }
    if (j == i) {
        return p;
    }
    return NULL;
}

// // 在指定位置插入元素（和单链表一样）
// bool ListInsert(CDNode* L, int i, int num){

// }

// 删除第i个节点
int ListDelete(CDNode* L, int i){
    if (i < 1) {
        return 0;
    }
    CDNode* p = GetElem(L, i - 1);
    if (p == NULL || p->next == L) {
        return 0;
    }
    CDNode* q = p->next; 
    p->next = q->next;
    q->next->prior = p;
}

//销毁
void DestroyList(CDNode** L){
    if (*L == NULL)
        return;
    CDNode* p = (*L)->next;
    CDNode* q;
    while(p!=*L){
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}

int main() {
    // 初始化
    CDNode* L = InitList();

    // 头插法
    int arr1[] = {1, 2, 3, 4, 5};
    CreateListHead(L, arr1, 5);
    printf("头插法: ");
    PrintListForward(L);

    // 尾插法
    DestroyList(&L);
    L = InitList();
    int arr2[] = {1, 2, 3, 4, 5};
    CreateListTail(L, arr2, 5);
    printf("尾插法: ");
    PrintListForward(L);

    // 反向遍历
    printf("反向遍历: ");
    PrintListBackward(L);

    // 按位查找
    CDNode* node = GetElem(L, 3);
    if (node)
        printf("第3个元素: %d\n", node->data);

    // 删除
    if (ListDelete(L, 2)) {
        printf("删除第2个元素后: ");
        PrintListForward(L);
    }

    // 销毁
    DestroyList(&L);

    return 0;
}