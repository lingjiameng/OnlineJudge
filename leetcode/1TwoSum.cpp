#include <iostream>
#include <vector>
#include <map>

using namespace std;



//关键思想，利用字典键值对特性
//字典的元素插入和搜索都是O(log(n))
//因此将　整数与下标 map，整体复杂度为O(nlog(n))
//如果用hashMap代替字典，复杂度会降至O(1)


vector<int> twoSum(vector<int> & nums, int target)
{
    map<int,int> delta;
    int numsLength  = nums.size();
    int diff;
    for(int i=0;i<=numsLength;i++){
        diff = target - nums[i];
        if ( delta.find(diff) != delta.end())
        {
            return {delta[diff],i};
        }
        else
        {
            delta[nums[i]] = i;
        }
    }
    return { };        
}

//数组初始化　{a,b,c}
//.end 指针不是最后一个元素的指针，而是最后一个元素额外指向的地址


int main(){
    vector<int> nums ={2, 7, 11, 15};
    vector<int> res = twoSum(nums, 9);
    cout<< res[0] << res[1] << endl;
    return 0;
}




