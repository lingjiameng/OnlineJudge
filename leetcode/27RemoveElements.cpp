#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int cur = 0, ptr = 0;
        for (; ptr < nums.size(); ptr++)
        {
            if (nums[ptr] != val)
                nums[cur++] = nums[ptr];
        }
        return cur;
    }
};