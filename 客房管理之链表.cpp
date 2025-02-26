#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cstring>

using namespace std;

// 定义客房链表结点结构
typedef struct HNode {
    char roomN[7];   // 客房名称
    float Price;     // 标准价格
    float PriceL;    // 入住价格(默认值=标准价格*80%)
    int Beds;        // 床位数
    char State[5];   // 入住状态(值域："空闲"、"入住"、"预订"，默认值为"空闲")
    struct HNode *next; // 指针域，指向下一个节点
} Hotel, *HLink;

// 函数声明
void Build(HLink &H);
void Exp(HLink H);
int Find(HLink &H, char *roomN);
void updateH(HLink &H, int beds, char *state);
void Add(HLink &H);
HLink FirstH(HLink &H);
void MoveK1(HLink &H, int k);
void ReverseN2(HLink &H);
void SortPriceL(HLink &H);
void upBed(HLink &H,int beds);

int main() {
    HLink H = nullptr;
    
    Build(H); // 创建客房信息链表
    printf("------------函数2:输出客房初始信息-------------\n");
    Exp(H); 

    printf("---------函数3:调用函数Find函数,查找客房名称-----------\n");
    int a = Find(H,"C103");
    if (a != 0) {
        printf("查找成功，所在位置为：第%d位\n", a);
    } else {
        printf("查找失败！没有找到此客房信息！");
    }

    printf("---------函数4:更新客房信息：将床位数为2的入住状态更新为入住状态-------------\n");
    updateH(H, 2, "入住"); // 更新床位数为2的客房状态为入住
    Exp(H); 

    printf("---------函数5:将该链表中未入住的客房入住价格均加价20%-------------\n");
    Add(H); 
    Exp(H); 

    printf("----------函数6:返回入住价格最高的客房结点指针，返回前将该结点在链表中删除--------\n");
    HLink h = FirstH(H); 
    Exp(H); 

    printf("----------函数7:将单链表中倒数第4个结点移到第一个结点位置--------\n");
    MoveK1(H, 4); 
    Exp(H); 

    printf("----------函数8:将单链表的正中间位置结点之后的全部结点倒置的功能--------\n");
    ReverseN2(H); 
    Exp(H); 

    printf("----------函数9:按照客房（入住价格，客房名称）升序排序--------\n");
    SortPriceL(H); 
    Exp(H); 

    printf("----------函数9:创建一个【床位数为beds的新结点】--------\n");
    int beds = 3;
    upBed(H, beds); 
    Exp(H); 

    return 0;
}

// 创建客房信息链表，从文件中读取数据
void Build(HLink &H) {
    ifstream infile("KeFangRuZhuSystem.txt");
    if (!infile) {
        cerr << "Unable to open file!" << endl;
        return;
    }

    H = new HNode; // 创建头节点
    H->next = NULL;
    HLink rear = H; // 用于追踪链表的最后一个节点

    char roomN[7];
    float price;
    int beds;

    // 从文件中读取数据并创建链表
    while (infile >> roomN >> price >> beds) {
        HLink newNode = new HNode;
        strcpy(newNode->roomN, roomN);
        newNode->Price = price;
        newNode->PriceL = price * 0.8f; // 入住价格为标准价格的 80%
        newNode->Beds = beds;
        strcpy(newNode->State, "空闲"); // 入住状态为 "空闲"
        newNode->next = nullptr;

        rear->next = newNode; // 将新节点连接到链表的末尾
        rear = newNode; // 更新链表的最后一个节点
    }
    infile.close();
}

// 输出所有客房信息
void Exp(HLink H) {
    HLink p = H->next; // 跳过头节点
    while (p) {
        printf("客房名称：%s    标准价格：%8.1f      入住价格：%8.1f      床位数：%d    入住状态：%s   \n", 
               p->roomN, p->Price, p->PriceL, p->Beds, p->State);
        p = p->next; // 移动到下一个节点
    }
}

// 查找指定客房名称的客房
int Find(HLink &H, char *roomN) {
    HLink p = H->next;
    int pos = 1; 
    while (p) {
        if (strcmp(p->roomN, roomN) == 0) { // 找到匹配的客房
            return pos;
        }
        p = p->next;
        pos++;
    }
    return 0; // 未找到返回0
}

// 更新指定床位数的客房状态
void updateH(HLink &H, int beds, char *state) {
    HLink p = H->next;
    while (p) {
        if (p->Beds == beds) {
            strcpy(p->State, state); // 更新状态
        }
        p = p->next;
    }
}

// 将未入住的客房价格加价20%
void Add(HLink &H) {
    HLink p = H->next;
    while (p) {
        if (strcmp(p->State, "空闲") == 0) {
            p->PriceL *= 1.2; // 加价20%
        }
        p = p->next;
    }
}

// 获取并删除价格最高的客房节点
HLink FirstH(HLink &H) {
    if (H == nullptr || H->next == nullptr) return nullptr; // 空链表或只有头节点

    HLink p = H->next; // 从第一个实际节点开始
    HLink maxNode = p; // 假设第一个节点是最大节点
    HLink prev = nullptr; // 当前节点的前一个节点
    HLink maxPrev = nullptr; // 最大节点的前一个节点

    while (p != nullptr) {
        if (p->PriceL > maxNode->PriceL) { // 找到更高价格的节点
            maxNode = p;
            maxPrev = prev;
        }
        prev = p;
        p = p->next;
    }

    // 从链表中删除 maxNode
    if (maxPrev == nullptr) {
        // maxNode 是第一个节点
        H->next = maxNode->next;
    } else {
        maxPrev->next = maxNode->next;
    }

    maxNode->next = nullptr; // 清除返回节点的 next 指针
    return maxNode; // 返回最大节点的指针
}

// 将单链表中倒数第k个结点移到第一个结点位置
void MoveK1(HLink &H, int k) {
    HLink fast;
    HLink slow;
    HLink prev = nullptr; // 跟踪slow的前一个结点
    fast = H->next;
    slow = H->next;
    int i = 0;
    // 先让fast指针指向第k个结点
    while (i < k) {
        fast = fast->next;
        i++;
    }
    // 同时移动两个指针，fast移动到末尾的同时，slow便指向了倒数第k个结点
    while (fast) {
        prev = slow;    // 用prev指针记录k之前的一个结点
        slow = slow->next;
        fast = fast->next;
    }
    if (prev != nullptr) {
        prev->next = slow->next; // 从链表中移除slow节点
        slow->next = H->next; // 将slow移到头节点之后
        H->next = slow; // 更新头指针
    }
}

// 将单链表的正中间位置结点之后的全部结点倒置
void ReverseN2(HLink &H) {
    HLink fast = H->next; // 快指针，走两步
    HLink slow = H->next; // 慢指针，走一步

    // 快慢指针找到链表中间节点
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    HLink current = slow->next; // 从中间节点之后开始反转
    HLink precurrent = nullptr;
    HLink nextNode;

    while (current) {
        nextNode = current->next; // 暂存下一个节点
        current->next = precurrent; // 反转当前节点指向
        precurrent = current; // 更新precurrent
        current = nextNode; // 移动到下一个节点
    }
    slow->next = precurrent; // 连接反转后的链表
}

// 按照入住价格和客房名称升序排序
void SortPriceL(HLink &H) {
    if (H == nullptr || H->next == nullptr) return; // 空链表或只有一个节点不需要排序

    HLink sorted = nullptr; // 新的已排序链表头
    HLink current = H->next; // 从第一个实际节点开始

    while (current) {
        HLink next = current->next; // 保存当前节点的下一个节点

        // 在 sorted 链表中找到插入位置
        if (sorted == nullptr || 
            sorted->PriceL > current->PriceL || 
            (sorted->PriceL == current->PriceL && strcmp(sorted->roomN, current->roomN) > 0)) {
            // 在 sorted 链表头插入
            current->next = sorted;
            sorted = current;
        } else {
            // 在 sorted 链表中找到插入位置
            HLink s = sorted;
            while (s->next != nullptr && 
                   (s->next->PriceL < current->PriceL || 
                   (s->next->PriceL  == current->PriceL && strcmp(s->next->roomN, current->roomN) < 0))) {
                s = s->next;
            }
            current->next = s->next; // 将当前节点插入到找到的位置
            s->next = current;
        }
        current = next; // 处理下一个节点
    }

    H->next = sorted; // 更新头节点的 next 指针指向排序后的链表
}

// 插入一个新节点，床位数为指定值
void upBed(HLink &H, int beds) {
    HLink newNode = new HNode; // 创建新节点
    cout << "请输入客房名称：";
    cin >> newNode->roomN;
    cout << "请输入标准价格：";
    cin >> newNode->Price;
    newNode->PriceL = newNode->Price * 0.8f; // 计算入住价格
    newNode->Beds = beds;
    strcpy(newNode->State, "空闲");
    newNode->next = nullptr;

    // 遍历链表找到插入位置
    HLink prev = H; // 从头节点开始
    HLink current = H->next;

    // 找到第一个床位数大于 beds 的位置
    while (current != nullptr && current->Beds <= beds) {
        prev = current;
        current = current->next;
    }

    // 插入新节点
    prev->next = newNode;
    newNode->next = current;
}