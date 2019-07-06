#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

//核心思想，仍然是遍历，但是要利用已有内存存储数据来进行遍历
//trick 每个值的标志应设为它实际代表的数，即只进行值的跳转

class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int s = nums.size();
        int jump, index; 
        // jump 记录要跳到的位置， index 记录当前顺序遍历的下一个下标
        for (int i = 0; i < s;)
        {
            index = i + 1;
            jump = nums[i];
            while (jump <= s && jump > 0 && nums[jump - 1] != jump)
            {   //循环跳转，直到越界或者已经确认过
                i = nums[jump - 1];
                nums[jump - 1] = jump; //用下标为n-1的位置,记录n是否存在
                jump = i;
            }
            i = index; //跳转完成，继续下一次跳转循环
        }
        for (int i = 0; i < s; i++)
            if (nums[i] != i + 1)
                return i + 1;
        return s + 1;
    }
};

int main()
{
    vector<int> nums = {3,4,-1,1};
    Solution mySol;
    cout<<mySol.firstMissingPositive(nums)<<endl;
    return 0;
}