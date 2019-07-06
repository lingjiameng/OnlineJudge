#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Sort{
public:
    void quickSortRecursive(vector<int> &nums,int left,int right){
        if(left >= right) return;
        int l=left, r=right;
        int key = nums[l++]; //选取最左值为中值
        while(l < r){
            while(l<r && nums[r]>  key) r--; //右侧找到小于等于中值的数
            while(l<r && nums[l]<= key) l++; //左侧找到大于中值的数
            swap(nums[l],nums[r]); //交换
        }
        if(nums[left] >= nums[l]) swap(nums[left],nums[l]); //左指针移动过，那么左指针的值一定小于等于中值
        else l--;//大于中值 则 左指针没有移动过，则正好符合顺序
        quickSortRecursive(nums,left,l-1);
        quickSortRecursive(nums,l+1,right);
    }

    void quickSortRecursive(vector<int> &nums)
    {
        //递归版本
        if(nums.size()==0)return;
        quickSortRecursive(nums,0,nums.size()-1);
    }

    void quickSort(vector<int> & nums){
        //非递归版本，通过栈实现,栈的大小log(n)
        if (nums.size() == 0)
            return;
        int istack[2*nums.size()];
        int sptr = 0; // stack pointer

        //入栈
        istack[sptr++] = 0;
        istack[sptr++] = nums.size()-1;
        
        while(sptr>0){
            int right = istack[--sptr], left = istack[--sptr];//出栈,记得先出右边界再出左边界
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
            istack[sptr++] = left;istack[sptr++] = l-1;
            istack[sptr++] = l+1 ;istack[sptr++] = right;
        }
    }
};

class Sort_readme
{
public:
    //快速排序，边分解边调整
    void quickSortRecursive(vector<int> &nums, int left, int right)
    {
        //cout<<left<<" "<<right<<endl;
        if (left >= right)
            return;
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
        // 算法步骤与分析
        //1)因为右指针先搜索，右指针只有两种情况会停下
        //   a)碰到 左指针 停下， 这时候的左指针或者是第一次还未搜索，或者是交换后的左指针
        //                                                          ( [1.a]会【进入步骤二结束】)
        //   b)找到 小于等于中值的数 停下, 【进入步骤二】
        //2)这时候左指针搜索
        //   a)碰到 右指针 停下，这时候的右指针实际有 [1.a] , [1.b]两种情况
        //         右指针 [1.a]情况: 左右指针指向左指针初始位置(可能大于中值) 【结束】
        //                             或者指向交换后的左指针(一定小于等于中值)  【结束】
        //         右指针 [1.b]情况: 左右指针都指向小于等于中值的数   【结束】
        //   b)找到 大于中值的数 停下，进行交换 并重复步骤一二 【循环】
        // 只有 1->a->2->b的情况会循环
        //
        //  1
        //  |->1a->2
        //  |     |->a 左右指针重合(一定),循环结束分两种情况:
        //        |               左右指针指向左指针初始位置(可能大于中值) 【结束】
        //        |               或者指向交换后的左指针(一定小于等于中值)  【结束】
        //  |     不会出现b
        //  |
        //  |->1b->2
        //        |->a 左右指针重合 且 指向小于等于中值的数【结束】
        //        |->b 【循环】->1
        //综上 结束时左右指针重合，【（值大于中值且左指针位于初始位置）或者 值小于等于中值(简单交换处理即可)】
        //左指针移动过，那么左指针指向的值一定小于等于中值
        if (nums[left] >= nums[l])
            swap(nums[left], nums[l]); //左指针移动过，那么左指针的值一定小于等于中值
        else
            l--; //左指针没有移动过，则可能是大于中值，正好符合顺序
        quickSortRecursive(nums, left, l - 1);
        quickSortRecursive(nums, l + 1, right);
    }
    void quickSortRecursive(vector<int> &nums)
    {
        quickSortRecursive(nums, 0, nums.size() - 1);
    }
};



int main()
{
    Sort mySort;
    vector<int> mynums = {-1, 0, 1, 2, -1, -4};
    mySort.quickSortRecursive(mynums);
    for(auto pt=mynums.begin();pt!=mynums.end();pt++)
    {
        cout<<*pt<<" ";
    }
    cout<<endl;

    return 0;
}