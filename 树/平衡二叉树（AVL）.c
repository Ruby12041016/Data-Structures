// AVL树的定义
// 1.平衡因子 = 左子树高度 - 右子树高度 
// 2.每个结点的平衡因子只能是 - 1, 0,1 
// 3.插入 / 删除后如果失衡，通过旋转重新平衡

#include <stdio.h>
#include <stdlib.h>

// AVL树结点
typedef struct AVLNode {
    int key;
    int height;  
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode, *AVLTree;

// 获取结点高度
int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// 获取平衡因子
int getBalanceFactor(AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 更新高度
void updateHeight(AVLNode* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 右旋（LL型）
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T3 = x->right;
    x->right = y;
    y->left = T3;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// 左旋（RR型）
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// 插入结点
AVLNode* insertAVL(AVLNode* root, int key) {
    // 正常的BST插入
    if (root == NULL) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        newNode->key = key;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->key) {
        root->left = insertAVL(root->left, key);
    } else if (key > root->key) {
        root->right = insertAVL(root->right, key);
    } else {
        return root;  
    }
    updateHeight(root);
    int balance = getBalanceFactor(root);
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// 中序遍历
void inorderAVL(AVLTree root) {
    if (root == NULL)
        return;
    inorderAVL(root->left);
    printf("%d(bf:%d) ", root->key, getBalanceFactor(root));
    inorderAVL(root->right);
}

int main() {
    AVLNode* root = NULL;
    int n, key;
    printf("请输入要插入的节点个数: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("请输入第%d个节点的值: ", i + 1);
        scanf("%d", &key);
        root = insertAVL(root, key);
    }
    printf("\n中序遍历结果: ");
    inorderAVL(root);
    printf("\n");
    printf("树高：");
    printf("%d\n", getHeight(root));
    return 0;
}