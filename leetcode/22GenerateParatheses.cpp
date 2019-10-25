#include <iostream>
#include <vector>
using namespace std;

class Solution
{
private:
    ///生成时按照限制生成可以节省一些时间
    void genRecursive(vector<string> &sols, string sol, int l, int r, int n)
    {
        //终止条件：拼接完成或者违法
        if (l < r || l > n || r > n)
            return; //非法配对
        if (l == r && l == n)
        { //生成一个合法子串
            sols.push_back(sol);
            return;
        }
        genRecursive(sols, sol + '(', l + 1, r, n);
        genRecursive(sols, sol + ')', l, r + 1, n);
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        genRecursive(result, "", 0, 0, n);
        return result;
    }
};

int main(){
    return 0;
}