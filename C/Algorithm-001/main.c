/*

题目描述:
二叉树序列化可以基于先序/中序/后序/层序等方式进行.
输入二叉树层次遍历序列,请输出其对应的先序遍历序列.

如有二叉树如下:
      0
    /   \
   1     2
  /       \
 3         4
  \       /
   5     6
其层序遍历序列为：0, 1, 2, 3, #, #, 4, #, 5, 6, #
其先序遍历序列为：0, 1, 3, #, 5, #, #, #, 2, #, 4, 6, #, #, #
(其中空用"#"代替)


输入描述:
第一行输入数字N为层序遍历结点个数
接下来以层序遍历顺序输入N行节点的值(空用"#"代替)
输出描述:
先序遍历结果(空打印为"#")

示例

输入

11
0
1
2
3
#
#
4
#
5
6
#

输出

0
1
3
#
5
#
#
#
2
#
4
6
#
#
#

*/

/*

说明：
此题的关键在于二叉树不同遍历序列转为另一种遍历序列序列时所采用的方法.
关于遍历序列的相互转换,通常不需要建立二叉树,可直接根据序列的特点进行转换.
对于层序,可以参照满二叉树在数组中的存储方式,
在读入数据时直接将其存储在数组对应的下标内.然后进行先序遍历时直接按照下标关系查找其儿子节点.
但这样对于一棵节点数不多但深度很深的二叉树,存储该树的数组会大量浪费,还可能出现内存不足的情况.
基于以上考虑,则可以使用一个字典来记录树中节点与数组内实际存储下标之间的关系,
这样,节点在数组中便可以紧挨着存储,不会浪费空间.
但是,在先序遍历时查找某个节点的儿子节点需要访问字典,通过字典的键值查找数组下标,
这样在遇到大量数据时无疑会大大增加时间复杂度,即使是哈希字典也会出现超时现象.
以上方法均不可行时,考虑最原始的方法,根据层序遍历建立一棵二叉树,然后对这颗树进行先序遍历,
这个最终的方案时通用方案,其他类似的遍历序列转换场景均可采用.

以下代码段一采用上面描述的字典、数组组合的方式构建二叉树,
代码段二采用建立经典二叉树的方法构建二叉树.

*/

//代码段一

#include <cstdio>
#include <unordered_map>

#define N 100010

using std::unordered_map;

char tree[N];
int n;
std::unordered_map<int, int> map;


int isOK(int i){
    if(map.count(i)==0){
        if(tree[map[i/2]]!='#'){
            map[i] = n;
            tree[n++]='#';
            return 1;
        }
        return 0;
    }
    return 1;
}

int main(){
    scanf("%d", &n);
    char s[4];
    map[0] = -1;
    //采用字典和数组构建二叉树
    for(int t=1,i=0; i<n; ++i){
        while(map.count(t/2)==0 || tree[map[t/2]]=='#')
            t+=2;
        scanf("%s\n", s);
        tree[i] = s[0];
        map[t++] = i;
    }

    //采用非递归
    int stack[1024], index = 0;
    int curr = 1;
    while(isOK(curr) || index){
        while(isOK(curr)){
            stack[index++] = curr;
            printf("%c\n", tree[map[curr]]);
            curr<<=1;
        }
        curr = stack[--index]*2+1;
    }
    return 0;
}




//代码段二

#include <stdio.h>
#include <stdlib.h>

#define N 100000

//二叉树数据结构
typedef struct TREE{
    char val[4];
    struct TREE *left;
    struct TREE *right;
}Tree;

int main(){
    int n;
    scanf("%d", &n);
    if(n==0){
        printf("#");
        return 0;
    }
    Tree* queue[N];
    int front, back;
    
    Tree *head = (Tree*)malloc(sizeof(Tree));
    head->left = head->right = NULL;
    scanf("%s", head->val);
    front=back=0;
    queue[back++]=head;
    Tree *node;
    //建树
    for(int i=1; i<n; ++i){
        node = (Tree*)malloc(sizeof(Tree));
        node->left = node->right = NULL;
        scanf("%s", node->val);
        while(front<back){
            if(queue[front]->val[0]!='#'){
                if(queue[front]->left==NULL){
                    queue[front]->left = node;
                    queue[back++] = node;
                    break;
                }
                else if(queue[front]->right==NULL){
                    queue[front]->right = node;
                    queue[back++] = node;
                    break;
                }
            }
            ++front;
        }
    }
    //非递归前序遍历
    int top=0;
    node = head;
    while(node || top){
        while(node){
            queue[top++] = node;
            printf("%s\n", node->val);
            if(node->val[0]!='#'){      //考虑在层序遍历过程中最下层叶子节点的儿子节点没有"#"来标记,
                                        //因此需要在此处将儿子节点的"#"添加进去
                if(node->left==NULL){
                    Tree *tmp = (Tree*)malloc(sizeof(Tree));
                    tmp->val[0] = '#';
                    tmp->val[1] = '\0';
                    tmp->left = tmp->right = NULL;
                    node->left = tmp;
                }
                if(node->right==NULL){
                    Tree *tmp = (Tree*)malloc(sizeof(Tree));
                    tmp->val[0] = '#';
                    tmp->val[1] = '\0';
                    tmp->left = tmp->right = NULL;
                    node->right = tmp;
                }
            }
            node = node->left;
        }
        node = queue[--top]->right;
    }
    
    return 0;
}