#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


//指针的移动一定要小心越界，仔细检查，左右都可能越界，检查后再使用指针
//sort(nums.begin(),nums.end()) 使用迭代器排序

class Solution
{
private:
    void quickSort(vector<int> & nums,int left ,int right){
        if(left >= right) return;
        int l=left,r=right;
        int key = nums[l++];
        while(l<r){
            while(l<r && nums[r]> key) r--;
            while(l<r && nums[l]<=key) l++;
            swap(nums[l],nums[r]);
        } 
        if(nums[l] <= key) swap(nums[left],nums[l]);
        else l--; 
        quickSort(nums,left,l-1);
        quickSort(nums,l+1,right);
    }
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        vector<vector<int>> sol;
        if(nums.size() < 4) return sol;
        quickSort(nums,0,nums.size()-1);
        for(int i = 0;i < nums.size()-3;i++){
            //i 去重，不能和i之前访问过的重复
            while(i>=1 && i < nums.size() && nums[i]==nums[i-1])i++; 
            for(int j=i+1;j<nums.size()-2;j++){
                //j 去重，不能和之前j访问过的重复
                while (j != i+1 && j<nums.size() && nums[j] == nums[j - 1])j++;
                //防止j过大，剩下的访问会越界,此时使用break
                if(j > nums.size()-2 )break;
                cout<<i<<'|'<<j<<endl;
                int sum = target - nums[i] - nums[j] , tmp = 0;
                int k = j+1, l = nums.size()-1;
                while (k < l)
                {   //有多个解
                    tmp = nums[k] + nums[l];
                    if (tmp == sum)
                    {
                        vector<int> tmpSol = {nums[i], nums[j], nums[k], nums[l]};
                        sol.push_back(tmpSol);
                        k++;
                        while (k < nums.size() && nums[k] == nums[k - 1])k++;
                    }
                    else if(tmp > sum)l--;
                    else k++;

                }
                
            }
        }
        return sol;
    }
    vector<vector<int>> fourSumBetter(vector<int> &nums, int target)
    {
        vector<vector<int>> res;
        int lens = nums.size();
        if (lens < 4)
            return res;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < lens - 3; ++i)
        {
            if (i != 0 && nums[i] == nums[i - 1])
                continue; // no duplication
            if (nums[i] + nums[lens - 3] + nums[lens - 2] + nums[lens - 1] < target)
                continue; // i too small
            if (target < nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3])
                break; // no solution

            for (int j = i + 1; j < lens - 2; ++j)
            {
                if (j != i + 1 && nums[j] == nums[j - 1])
                    continue; // no duplication
                if (nums[i] + nums[j] + nums[lens - 2] + nums[lens - 1] < target)
                    continue; // i too small
                if (target < nums[i] + nums[j] + nums[j + 1] + nums[j + 2])
                    break; // no solution

                int head = j + 1;
                int tail = lens - 1;
                int val = target - nums[i] - nums[j];
                while (head < tail)
                {
                    int sum = nums[head] + nums[tail];
                    if (sum < val)
                        ++head;
                    else if (val < sum)
                        --tail;
                    else
                    {
                        res.push_back({nums[i], nums[j], nums[head], nums[tail]});
                        // do {++head;} while(head < tail && nums[head] == nums[head-1]);
                        // do {--tail;} while(head < tail && nums[tail] == nums[tail+1]);

                        while (head < tail && nums[head] == nums[++head])
                            ;
                        while (head < tail && nums[tail] == nums[--tail])
                            ;

                        // while(head < tail && nums[head] == nums[head+1]) ++head;
                        // while(head < tail && nums[tail] == nums[tail-1]) --tail;
                        // ++head; --tail;
                    }
                }
            }
        }
        return res;
    }
};

int main(){
    Solution mySol; // -5 -4 -3 1 1 1 2
    vector<int> question = {1, -5, 1, -4, 2, 1, -3};
    auto res = mySol.fourSum(question,1);
    // cout<<"!!"<<endl;
    for (auto pt = res.begin(); pt != res.end(); pt++)
    {   
        cout <<"[ ";
        for(auto p = pt->begin();p !=pt->end(); p++) 
            cout << *p << " ";
        cout<<']'<<endl;
    }
    return 0;
    return 0;
}