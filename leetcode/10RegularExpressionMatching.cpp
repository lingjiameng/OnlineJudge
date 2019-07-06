#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
/*
初始化 s[0..0] 与 p[0..0]空串匹配

动态规划dp
s[i] i>=1  
p[j] j>=1
dp[i][j] whther s[0..i] match with p[0..j]

真值进行传递
if p[j] != "*":正常匹配，p[j]==s[i] and  dp[i-1][j-1]

if p[j] == "*":分情况讨论
    if * 代表0次重复:  
        即 [.*] 忽略掉， 相当于dp[i][j-2]

    if * 代表1次或以上重复： 
        那么等效于(p[0..j]与s[0..i-1]匹配， 并且p[j]==s[i])
        也就是如果一次或以上重复成功匹配的话， p[0..j] 一定与 s[0..i-1] 匹配（此时*代表零次及以上重复，如果前面是n次重复，这里就是n-1次重复），不过这是充分条件。 充要条件需要再加上 s[i] == p[j-1]

    即 * 代表 n次重复匹配(dp[i][j]==1)，等效于(n-1次重复和s[i-1]匹配（dp[i-1][j]==1），并且 再额外匹配一次 s[i]==p[j-1])
    特例在于当 n为0时， 等效于dp[i][j-2]是否匹配

*/


class Solution
{
public:
    bool isMatch(string s, string p)
    {
        s= "@"+s;
        p= "@"+p;
        int sLength = s.size();
        int pLength = p.size();

        vector<vector<bool>> dp(sLength,vector<bool>(pLength,false));
        dp[0][0]=true;

        for(int i=0;i<sLength;i++)
        {
            cout << "!!" << endl;
            for (int j=1;j<pLength;j++)
            {
                if (p[j] !='*') //匹配的位不为*
                {

                    dp[i][j] = ((p[j] == '.' && s[i]!='@') || s[i] == p[j]) && ( (i==0 && j==0) || dp[i - 1][j - 1]) ;
                    cout << "matching" << i << " " << j <<" result: "<<dp[i][j]<< endl;
                }
                else //匹配的位为*
                {
                    //dp[i][j] = dp[i][j-2]; //0次匹配
                    //dp[i][j] = dp[i-1][j] && s[i] == p[j]; //1次及以上匹配
                    dp[i][j] = dp[i][j - 2] || ((i > 0 && dp[i - 1][j]) && ((p[j-1] == '.' && s[i] != '@') || s[i] == p[j - 1])); //0次及以上匹配
                    cout << "matching*" << i << " " << j << " result: " << dp[i][j] << endl;
                }
            }
        }
       

        for (int i = 0; i < sLength; i++)
        {
            for (int j = 0; j < pLength; j++)
            {
                cout<< dp[i][j]<<" ";
            }
            cout<<endl;
        }

        return dp[sLength-1][pLength-1];
    }
};
class Solution2
{
public:
    bool isMatch(string s, string p)
    {
        s = "@" + s; p = "@" + p; //add @ in head for empty string
        int sLength = s.size(), pLength = p.size();
        vector<vector<bool>> dp(sLength, vector<bool>(pLength, false));
        dp[0][0] = true;

        for (int i = 0; i < sLength; i++)
        {
            for (int j = 1; j < pLength; j++)
            {
                if (p[j] != '*') //匹配的位不为*
                {
                    //一定与非空字符串匹配 ==> i>0
                    //p[j]和s[i]对应匹配  ==> (p[j] == '.' || s[i] == p[j])
                    //s[0..i-1] p[0..j-1]匹配 ==> dp[i-1][j-1]
                    dp[i][j] = i>0 && (p[j] == '.' ||s[i] == p[j]) && dp[i - 1][j - 1];
                }
                else //匹配的位为*
                {
                    //0次匹配,可能会与空字符串匹配 ==> dp[i][j] = dp[i][j-2];
                    //1次及以上匹配，不会与空串匹配 ==> i > 0 && dp[i-1][j] && s[i] == p[j-1];
                    dp[i][j] = dp[i][j - 2] || (i > 0 && dp[i - 1][j] && (p[j-1] == '.' || s[i] == p[j-1])); //0次及以上匹配
                }
            }
        }
        return dp[sLength - 1][pLength - 1];
    }
};

class Solution_Shortest
{
public:
    bool isMatch(string s, string p)
    {
        s = "@" + s; p = "@" + p; //add @ in head for empty string
        int sLength = s.size(), pLength = p.size();
        vector<vector<bool>> dp(sLength, vector<bool>(pLength, false));
        dp[0][0] = true;
        for (int i = 0; i < sLength; i++)
            for (int j = 1; j < pLength; j++)
                if (p[j] != '*') dp[i][j] =  i > 0 && (p[j] == '.' || s[i] == p[j]) && dp[i - 1][j - 1];
                else dp[i][j] = dp[i][j - 2] || (i > 0 && dp[i - 1][j] && (p[j - 1] == '.' || s[i] == p[j - 1]));
        return dp[sLength - 1][pLength - 1];
    }
};

int main()

{
    //左值引用与右值引用的区别
    // int i = 42;
    // int &ri = i;
    // int *pi = &i;
    // int &rpi1 = *pi;
    // //int &&ri2 = *pi;
    // int *pi1 = &ri;
    
    // int *&rpi = pi;
    // //int *&rpi1 = &i;
    // int *&&rpi2 = &i;
    // //int &*pri = &ri;
    Solution_Shortest mySol;
    string re = "a*";
    // cout<< ('*'==re[1])<<endl;
    cout<<mySol.isMatch("aaab","a*.b*")<<endl;

    return 0;
}