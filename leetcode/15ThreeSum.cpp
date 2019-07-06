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
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        //O(nlogn)排序
        //O(n)*O(n),固定一个数，并且剩余的数双指针搜索两数和
        //增加while循环跳过重复情况
        int i = 0, j = 0, k = 0, l = nums.size();
        quickSort(nums);
        vector<vector<int>> ans;
        for (; i < l && nums[i] <= 0; i++) //一定要加上 nums[i]<=0,会少搜索很多情况
        {
            int target = -nums[i];
            for (j = i + 1, k = l - 1; j < k && nums[k] >= 0;)
            {
                int sum = nums[j] + nums[k];
                if (target == sum)
                {
                    ans.push_back({nums[i], nums[j], nums[k]});
                    while (k > j && nums[k] == nums[k - 1])
                        k--;
                    while (j < k && nums[j] == nums[j + 1])
                        j++;
                    k--;
                    j++;
                }
                else if (target > sum)
                {
                    j++;
                }
                else if (target < sum)
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

class SolutionOn3
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
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        //暴力搜索,超时O(n^3)
        int i = 0, j = 0, k = 0, l = nums.size();
        quickSort(nums);
        vector<vector<int>> ans;
        for (; i < l; i++)
        {
            for (j = i + 1; j < l; j++)
            {
                for (k = j + 1; k < l; k++)
                {
                    if (0 == nums[i] + nums[j] + nums[k])
                    {
                        ans.push_back({nums[i], nums[j], nums[k]});
                    }
                    while (k < l - 1 && nums[k] == nums[k + 1])
                        k++;
                }
                while (j < l - 1 && nums[j] == nums[j + 1])
                    j++;
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
    vector<vector<int>> ans = mySol.threeSum(nums);

    for (auto pt = ans.begin(); pt != ans.end(); pt++)
    {
        for (auto pt2 = (*pt).begin(); pt2 != (*pt).end(); pt2++)
        {
            cout << *pt2 << " ";
        }
        cout << endl;
    }

    return 0;
}