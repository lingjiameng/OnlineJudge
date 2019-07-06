#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;
class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        string ans = "";
        if(0 == strs.size())return ans;
        for(int l=0; l< strs[0].size();l++){
            for (int i = 0; i < strs.size(); i++)
            {
                if(strs[i][l]!=strs[0][l])
                    return ans;
            }
            ans+=strs[0][l];
        }
        return ans;
    }
};
int main()
{
    vector<string> strs ={"sdsd","sef"};
    Solution mySol;
    cout<< mySol.longestCommonPrefix(strs)<<endl;
    return 0;
}