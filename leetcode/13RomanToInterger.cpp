#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
/*
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/
class Solution
{
private:
    int comp(int a, int b){
        if(a<b) return -a;
        return a;   
    }

public:
    int romanToInt(string s)
    {
        map<char, int> r2t = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
        };
        int ans=0;
        for(int i=0 ; i<s.size()-1 ; i++)
            //只有当前字母小于后一个字母时，减当前值，其余情况加当前值
            ans += comp(r2t[s[i]],r2t[s[i+1]]);
        ans += r2t[s.back()];
        return ans;
    }
};

int main()
{
    Solution mySol;
    while (1)
    {
        string num;
        cin >> num;
        cout << mySol.romanToInt(num) << endl;
    }
    return 0;
}