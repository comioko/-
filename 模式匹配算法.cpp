#include <stdio.h>
#include <string.h>

#define MAXSIZE 100  // 定义主串和子串的最大长度

// 朴素的模式匹配算法
void BFMatch(const char *text, const char *pattern, int pos) {
    int n = text[0];  //主串的长度
    int m = pattern[0];  //子串的长度
    int i = pos+1;  // 从主串的第pos位置开始匹配
    int j = 1;  //从子串的第一个字符开始匹配
    int compCount=0, passCount=1;

    while (i <= n && j <= m) {  // 当主串和子串都未匹配完时
        if (text[i] == pattern[j]) {  
            i++;
            j++;
        } else {
            printf("第%d趟匹配\n",passCount);
            printf("主串：");
            printf("%s\n",text+1);
            printf("子串：");
            for(int x=1;x<passCount;x++)
                printf(" ");           //使子串对齐到最新匹配位置
            printf("%s\n",pattern+1);
            printf("主串指针从%d移到%d\n",i-j+1,i);
            printf("子串指针从1移到%d,比较了%d次\n",j,j);
            compCount=compCount+j;  // 更新比较次数
            i=i-j+2;            //调整主串的起始位置，向右移动一位
            j=1;              //子串重新开始匹配
            passCount++; 
        }
    }
    printf("第%d趟匹配\n",passCount);
    printf("主串：");
    printf("%s\n",text+1);
    printf("子串：");
    for(int x=1;x<passCount;x++)
        printf(" ");
    printf("%s\n",pattern+1);

    printf("主串指针从%d移到%d\n",i-j+1,i);
    printf("子串指针从1移到%d,比较了%d次\n",j,j);
    compCount=compCount+j-1;    // 更新比较次数
    if(j>m){  
        printf("匹配成功，匹配成功时的位置序号为%d\n",i-m);
        printf("匹配总趟数为%d\n",passCount);
        printf("匹配总比较次数为%d\n",compCount);
    }
    else
        printf("匹配失败！！！\n");
}

// 计算Next数组
void getNext(const char *pattern, int next[]) {
    int m = pattern[0];  // 子串的长度
    int i = 1, j = 0;
    next[1] = 0;  // 初始化第一个位置的next值为0
    while (i < m) {
        if (j == 0 || pattern[i] == pattern[j]) {  // 匹配成功或j为0时
            i++;
            j++;
            next[i] = j;  // 更新next数组
        } else {
            j = next[j];  // 利用next数组进行回退
        }
    }
}

// 计算NextVal数组
void getNextval(const char *pattern, int nextval[]) {
    int m = pattern[0];  // 子串的长度
    int i = 1, j = 0;
    nextval[1] = 0;  // 初始化第一个位置的nextval值为0
    while (i < m) {
        if (j == 0 || pattern[i] == pattern[j]) {  // 匹配成功或j为0时
            i++;
            j++;
            if (pattern[i] != pattern[j]) {
                nextval[i] = j;  // 如果字符不相等，直接赋值
            } else {
                nextval[i] = nextval[j];  // 如果字符相等，使用nextval值
            }
        } else {
            j = nextval[j];  // 利用nextval数组进行回退
        }
    }
}
// KMP算法实现
void Index_KMP_next(const char *text, const char *pattern, int pos, int next[]) {
    int n = text[0];  //主串的长度
    int m = pattern[0];  //子串的长度
    int i=pos+1, j=1;  // 初始化主串和子串的指针        *********
    int t=0;      // 记录子串指针位置
    int compCount=0, passCount=1;  // 比较次数和总趟数 

    while (i <= n && j <= m) {  // 当主串和子串都未匹配完时
        if (j == 0 || text[i] == pattern[j]) {  // 如果字符匹配或j为0
            ++i;
            ++j;
        } else {
            printf("第%d趟匹配\n",passCount);
            printf("主串：");
            printf("%s\n",text+1);
            printf("子串：");
            for(int x=0;x<i-j;x++)
                printf(" ");
            printf("%s\n",pattern+1);
            if(t==0){
                printf("主串指针从%d移到%d\n",i-j+t+1,i);
                printf("子串指针从%d移到%d,比较了%d次\n",t+1,j,j-t);
                compCount=compCount+j-t;
            }else{
                printf("主串指针从%d移到%d\n",i-j+t,i);
                printf("子串指针从%d移到%d,比较了%d次\n",t,j,j-t+1);
                compCount=compCount+j-t+1;
            }
            j = next[j];  // 利用next数组进行回退
            t=j;
            (passCount)++;  // 增加总趟数
        }
    } 
    printf("第%d趟匹配\n",passCount);
    printf("主串：");
    printf("%s\n",text+1);
    printf("子串：");
    for(int x=0;x<i-j;x++)
        printf(" ");
    printf("%s\n",pattern+1);
    if(t==0){
        printf("主串指针从%d移到%d\n",i-j+t+1,i);
        printf("子串指针从%d移到%d,比较了%d次\n",t+1,j,j-t-1);
        compCount=compCount+j-t-1;
    }else{
        printf("主串指针从%d移到%d\n",i-j+t,i);
        printf("子串指针从%d移到%d,比较了%d次\n",t,j,j-t);
        compCount=compCount+j-t;
    }
    if(j>m){  // 如果子串匹配完成
        printf("匹配成功，匹配成功时的位置序号为%d\n",i-m);
        printf("匹配总趟数为%d\n",passCount);
        printf("匹配总比较次数为%d\n",compCount);
    }
    else
        printf("匹配失败！！！\n");
}
void Index_KMP_nextval(const char *text, const char *pattern, int pos, int next[]) {
    int n = text[0];  //主串的长度
    int m = pattern[0];  //子串的长度
    int i=pos+1, j=1;  // 初始化主串和子串的指针        *********
    int t=0;      // 记录子串指针位置
    int compCount=0, passCount=1;  // 比较次数和总趟数 

    while (i <= n && j <= m) {  // 当主串和子串都未匹配完时
        if (j == 0 || text[i] == pattern[j]) {  // 如果字符匹配或j为0
            ++i;
            ++j;
        } else {
            printf("第%d趟匹配\n",passCount);
            printf("主串：");
            printf("%s\n",text+1);
            printf("子串：");
            for(int x=0;x<i-j;x++)
                printf(" ");
            printf("%s\n",pattern+1);
            if(t==0){
                printf("主串指针从%d移到%d\n",i-j+t+1,i);
                printf("子串指针从%d移到%d,比较了%d次\n",t+1,j,j-t);
                compCount=compCount+j-t;
            }else{
                printf("主串指针从%d移到%d\n",i-j+t,i);
                printf("子串指针从%d移到%d,比较了%d次\n",t,j,j-t+1);
                compCount=compCount+j-t+1;
            }
            j = next[j];  // 利用next数组进行回退
            t=j;
            (passCount)++;  // 增加总趟数
        }
    } 
    printf("第%d趟匹配\n",passCount);
    printf("主串：");
    printf("%s\n",text+1);
    printf("子串：");
    for(int x=0;x<i-j;x++) printf(" ");
    printf("%s\n",pattern+1);
    if(t==0){
        printf("主串指针从%d移到%d\n",i-j+t+1,i);
        printf("子串指针从%d移到%d,比较了%d次\n",t+1,j,j-t-1);
        compCount=compCount+j-t-1;
    }else{
        printf("主串指针从%d移到%d\n",i-j+t,i);
        printf("子串指针从%d移到%d,比较了%d次\n",t,j,j-t);
        compCount=compCount+j-t;
    }
    if(j>m){  //如果子串匹配完成
        printf("匹配成功，匹配成功时的位置序号为%d\n",i-m);
        printf("匹配总趟数为%d\n",passCount);
        printf("匹配总比较次数为%d\n",compCount);
    }
    else
        printf("匹配失败！！！\n");
}


int main() {
    int choice;
    char text[MAXSIZE + 1];  // 主串，多一个位置用于存储长度
    char pattern[MAXSIZE + 1];  // 子串，多一个位置用于存储长度
    int pos;  // 匹配起始位置
    int start;  // 匹配起始位置的结果
    int next[MAXSIZE + 1];  // Next数组
    int nextval[MAXSIZE + 1];  // NextVal数组
    

    while (1) {
        printf("菜单：\n");
        printf("1. 输入主串、子串和匹配起始位置\n");
        printf("2. 朴素的模式匹配算法\n");
        printf("3. KMP改进算法(Next[])\n");
        printf("4. KMP改进算法(NextVal[])\n");
        printf("0. 退出管理系统\n");
        printf("请输入你要选择的功能(0-4): ");
        scanf("%d", &choice);

        if (choice < 0 || choice > 4) {
            printf("输入错误，请重新输入！\n");
            continue;
        }

        switch (choice) {
            case 1: {
                printf("请输入主串：\n");
                scanf("%s", text + 1);  // 输入主串，跳过第一个位置
                text[0] = strlen(text + 1);  // 存储主串长度
                printf("请输入子串：\n");
                scanf("%s", pattern + 1);  // 输入子串，跳过第一个位置
                pattern[0] = strlen(pattern + 1);  // 存储子串长度
                printf("输入匹配起始位置pos的值（从0开始）:\n");
                scanf("%d", &pos);
                if ( pos > text[0]) {
                    printf("起始位置无效，请输入有效的起始位置。\n");
                    break;
                }
                break;
            }
            case 2: {
                printf("2.朴素的模式匹配算法\n");
                BFMatch(text, pattern, pos);
                break;
            }
            case 3: {
                printf("3.KMP改进算法(Next[])\n");
                getNext(pattern, next);  // 计算Next数组
                printf("Next数组: ");
                for (int i = 1; i <= pattern[0]; i++) {
                    printf("%d ", next[i]);  // 打印Next数组
                }
                printf("\n");
                Index_KMP_next(text, pattern, pos, next);
                break;
            }
            case 4: {
                printf("4. KMP改进算法(NextVal[])\n");
                getNextval(pattern, nextval);  // 计算NextVal数组
                printf("NextVal数组: ");
                for (int i = 1; i <= pattern[0]; i++) {
                    printf("%d ", nextval[i]);  // 打印NextVal数组
                }
                printf("\n");
                Index_KMP_nextval(text,pattern, pos, nextval);
                break;
            }
            case 0:
                printf("退出成功!\n");
                return 0;
            default:
                printf("输入错误，请重新输入！\n");
        }
    }
    return 0;
}