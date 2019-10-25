#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void cout_nums(const vector<int> &nums){
    for(int i=0;i<nums.size();i++)
        cout <<nums[i]<<" ";
    cout <<endl;
}

void perm(int depth, vector<int> &nums, vector<vector<int>> &perms)
{
    if (depth >= nums.size())
    {
        perms.push_back(vector<int>(nums.begin(), nums.end()));
        return;
    }
    for (int i = depth; i < nums.size(); i++)
    {
        swap(nums[depth], nums[i]);
        perm(depth + 1, nums, perms);
        swap(nums[depth], nums[i]);
    }
}

void perm(vector<int> &nums, vector<vector<int>> &perms)
{
    perm(0, nums, perms);
}

int main(){

    vector<int> nums;
    vector<vector<int>> permutations;
    for(int i=0;i<4;i++)
        nums.push_back(i);

    // sort(nums.begin(),nums.end()); //按照从小到大的顺序排序
    // permutations.push_back(vector<int>(nums.begin(),nums.end()));
    // while(next_permutation(nums.begin(),nums.end()))
    //     permutations.push_back(vector<int>(nums.begin(), nums.end()));


    perm(nums,permutations);

    for(int i=0;i<permutations.size();i++)
        cout_nums(permutations[i]);

    return 0;
}