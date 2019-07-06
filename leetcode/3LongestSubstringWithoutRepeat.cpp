#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

//使用字典时间复杂度O(nlogn)
//使用固定大小的矩阵复杂度O(n)
//思路，最大子串分解为动态规划问题
// 建立字母表矩阵，元素为上一次出现的下标
// 顺序搜索字符串，只需向前查找不重复的最小下标即可
// tips: 最小下标 = max(上一次的最小下标，当前新字符上一次出现的位置+1)
// 这就将问题分解为了子问题。上一次的最小下标可记录;上一次位置可通过矩阵O(1)查找.
//最终只需要一遍搜索即可完成
int lengthOfLongestSubstring(string s)
{
    int indices[256];
    memset(indices,-1,sizeof(indices));
    int strLength = s.size();
    int maxLength = -1; // 已记录的最大长度
    int minindex = 0;   // 上一次搜索无重复的最小下标
    for(int i=0 ; i<strLength; i++){
        minindex = max(indices[int(s[i])]+1 , minindex);
        maxLength = max(maxLength, i - minindex);
        indices[int(s[i])]=i;
    }
    return maxLength+1;
}

int main()
{
    cout<<lengthOfLongestSubstring("abcabcabc")<<endl;
    return 0;
}