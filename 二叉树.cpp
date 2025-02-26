#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

// 定义二叉树结点结构体
typedef struct node {
    char data; // 数据域
    struct node *lchild, *rchild; // 左右孩子指针
} BinTNode, *BinTree; // 树中结点类型

// 函数声明
void CreateBiTree(BinTree &T);
void PreOrderTraverse(BinTree &T);
void InOrderTraverse(BinTree &T);
void PostOrderTraverse(BinTree &T);
void LevelOrderTraverse(BinTree &T);
int findPath(BinTree T, char target, char path[], int pathLen);

int main() {
    BinTree T = NULL; // 初始化二叉树为空
    int choice; // 用户选择变量

    char target = 'B'; // 目标节点
    char path[100]; // 存储路径的数组

    while (1) {
        // 打印菜单
        cout << "菜单：\n1.建立二叉树存储结构\n2.求二叉树的先序遍历\n3.求二叉树的中序遍历\n4.求二叉树的后序遍历\n5.求二叉树的层次遍历\n6.求给定结点的路径\n0.退出系统\n";
        cout << "请选择：\n";
        cin >> choice; // 输入选择
        if (choice > 6 || choice < 0) {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        switch (choice) {
            case 1:
                // 建立二叉树存储结构
                cout << "请输入一个二叉树(#代表空):" << endl;
                CreateBiTree(T);
                break;
            case 2:
                // 二叉树的先序遍历
                PreOrderTraverse(T);
                cout << endl;
                break;
            case 3:
                // 二叉树的中序遍历
                InOrderTraverse(T);
                cout << endl;
                break;
            case 4:
                // 二叉树的后序遍历
                PostOrderTraverse(T);
                cout << endl;
                break;
            case 5:
                // 二叉树的层次遍历
                LevelOrderTraverse(T);
                cout << endl;
                break;
            case 6:
                // 求给定结点的路径
                cout << "从根节点到节点 " << target << " 的路径为：";
                if (!findPath(T, target, path, 0)) {
                    cout << "节点不存在\n" << endl;
                }
                break;
            case 0:
                // 退出系统
                printf("成功退出系统！\n");
                return 0;
            default:
                printf("输入错误！，请重新输入！\n");
                break;
        }
    }
    return 0;
}
// 创建二叉树
void CreateBiTree(BinTree &T) {
    char ch;
    cin >> ch; // 输入字符
    if (ch == '#') {
        T = NULL; // 如果输入为#，则当前节点为空
    } else {
        T = new BinTNode; // 创建新节点
        T->data = ch; // 赋值数据域
        CreateBiTree(T->lchild); // 递归创建左子树
        CreateBiTree(T->rchild); // 递归创建右子树
    }
}

// 先序遍历
void PreOrderTraverse(BinTree &T) {
    if (T) {
        cout << T->data; // 访问根节点
        PreOrderTraverse(T->lchild); // 先序遍历左子树
        PreOrderTraverse(T->rchild); // 先序遍历右子树
    }
}

// 中序遍历
void InOrderTraverse(BinTree &T) {
    if (T) {
        InOrderTraverse(T->lchild); // 中序遍历左子树
        cout << T->data; // 访问根节点
        InOrderTraverse(T->rchild); // 中序遍历右子树
    }
}

// 后序遍历
void PostOrderTraverse(BinTree &T) {
    if (T) {
        PostOrderTraverse(T->lchild); // 后序遍历左子树
        PostOrderTraverse(T->rchild); // 后序遍历右子树
        cout << T->data; // 访问根节点
    }
}

// 层次遍历
void LevelOrderTraverse(BinTree &T) {
    if (T) {
        BinTree queue[100]; // 定义队列用于存储节点
        int front = 0, rear = 0; // 队列的头尾指针
        queue[rear++] = T; // 根节点入队
        while (front < rear) {
            BinTree node = queue[front++]; // 队头节点出队
            cout << node->data; // 访问节点
            if (node->lchild) queue[rear++] = node->lchild; // 左孩子入队
            if (node->rchild) queue[rear++] = node->rchild; // 右孩子入队
        }
    }
}

// 查找从根节点到目标节点的路径
int findPath(BinTree T, char target, char path[], int pathLen) {
    if (!T) return 0; // 如果节点为空，返回0
    path[pathLen] = T->data; // 将当前节点加入路径
    pathLen++; // 路径长度加1
    if (T->data == target) { // 如果找到目标节点
        for (int i = 0; i < pathLen; i++) {
            printf("%c ", path[i]); // 打印路径
        }
        return 1; // 返回1表示找到
    }
    // 递归查找左子树或右子树
    if (findPath(T->lchild, target, path, pathLen) || findPath(T->rchild, target, path, pathLen)) {
        return 1; // 如果找到，返回1
    }
    return 0; // 如果未找到，返回0
}