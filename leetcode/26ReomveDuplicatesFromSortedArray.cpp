#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        int cnt = 0, ptr = 0;
        while (ptr < nums.size())
        {
            while (nums[ptr] == nums[cnt])
            {
                ptr++;
                if (ptr >= nums.size())
                    return cnt + 1;
            }
            nums[++cnt] = nums[ptr];
        }
        return cnt + 1;
    }
};