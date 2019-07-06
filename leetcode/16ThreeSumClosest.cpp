#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Solution
{
private:
    void quickSort(vector<int> &nums)
    {
        //非递归版本，通过栈实现,栈的大小log(n)
        if (nums.size() == 0)
            return;
        int istack[2 * nums.size()];
        int sptr = 0; // stack pointer

        //入栈
        istack[sptr++] = 0;
        istack[sptr++] = nums.size() - 1;

        while (sptr > 0)
        {
            int right = istack[--sptr], left = istack[--sptr]; //出栈,记得先出右边界再出左边界
            if (left >= right)
                continue;

            int l = left, r = right;
            int key = nums[l++]; //选取最左值为中值
            while (l < r)
            {
                while (l < r && nums[r] > key)
                    r--; //右侧找到小于等于中值的数
                while (l < r && nums[l] <= key)
                    l++;                //左侧找到大于中值的数
                swap(nums[l], nums[r]); //交换
            }
            if (nums[left] >= nums[l])
                swap(nums[left], nums[l]); //左指针移动过，那么左指针的值一定小于等于中值
            else
                l--; //左指针没有移动过，则可能是大于等于等于中值，正好符合顺序
            //入栈
            istack[sptr++] = left;
            istack[sptr++] = l - 1;

            istack[sptr++] = l + 1;
            istack[sptr++] = right;
        }
    }

public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        //O(nlogn)排序
        //O(n)*O(n),固定一个数，并且剩余的数双指针搜索两数和
        //增加while循环跳过重复情况
        int i = 0, j = 0, k = 0, l = nums.size();
        quickSort(nums);

        int ans=nums[0]+nums[1]+nums[2];
        int error = abs(ans-target);

        for (; i < l; i++)
        {
            int twoSum = target - nums[i];
            
            for (j = i + 1, k = l - 1; j < k ;)
            {
                int sum = nums[j] + nums[k];
                int tmperr = sum - twoSum;
                if( abs(tmperr) < error){
                    ans = target+tmperr;
                    error = abs(tmperr);
                }
                if (0 == tmperr)
                {
                    return target;
                }
                else if (0 > tmperr)
                {
                    j++;
                }
                else if (0 < tmperr)
                {
                    k--;
                }
            }
            while (i < l - 1 && nums[i] == nums[i + 1])
                i++;
        }
        return ans;
    }
};

int main()
{
    Solution mySol;
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    int ans = mySol.threeSumClosest(nums, 5);

    cout<<ans<<endl;

    return 0;
}