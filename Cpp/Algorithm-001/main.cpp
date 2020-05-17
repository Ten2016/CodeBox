/*

题目描述:
已知某一个字母序列,把序列中的字母按出现顺序压入一个栈.
在入栈的任意过程中,允许栈中的字母出栈,求所有可能的出栈顺序.

输入描述:
字符串.    如: abc
输出描述:
可能的出栈顺序,每行一种顺序.


示例

输入
abc
输出
abc
acb
bac
bca
cba

*/

/*

说明：
此题之所以记录在此,是因为这道题目是全排列和判断是否合法出栈顺序的结合.
在某些场景下经常会用到栈,那么判断出栈顺序则经常使用,这题是栈的综合应用.
另外,全排列是一个经典的回溯问题,其解法非常典型,平时也会经常使用.

*/


#include <iostream>
#include <string>
#include <stack>

using namespace std;

//交换s[i]与s[j]
void swap(string &s, int i, int j){
    auto c = s[i];
    s[i] = s[j];
    s[j] = c;
}

//判断是否是合法的出栈顺序
bool isvalid(const string &str, const string &ans){
    stack<char> sc;
    int i=0, j=0;
    while(i<str.size()){
        sc.push(str[i++]);
        while(!sc.empty() && sc.top()==ans[j]){
            sc.pop();
            ++j;
        }
    }
    return sc.empty();
}

//回溯进行全排列
void backtrack(const string &str, string &ans, int a){
    int len = str.size()-1;
    if(a==len && isvalid(str, ans)){
        cout<<ans<<endl;
        return ;
    }
    for(int k=a; k<=len; ++k){
        swap(ans, a, k);
        backtrack(str, ans, a+1);
        swap(ans, a, k);
    }
}

int main(){
    string str, ans;
    cin>>str;
    ans = str;
    backtrack(str, ans, 0);
    
    return 0;
}
