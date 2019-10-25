#include<iostream>
#include <vector>
using namespace std;

//给定一个数组，将其中元素分为两组，两组元素个数相差不能超过（ delta <= 1 ），
//求 两组元素分别求和，然后 和的差值的最小值。

//解法，将问题转换为背包问题，目的是求出 sum/2 -累计和 的最小值
//最优解时一定会将数组分为两部分，其中一部分元素个数为N/2，并且和小于等于并最接近 所有元素和的一半。

// 构造动归数组 dp[i][j] = sum_left,表示前i个物体放入j个物体时和目标和差值的最小值,（出现负值全部忽略）
// dp[i][j] = min(dp[i][j-1] - nums[i], dp[i-1][j])

// dp[i][j][w] = max(dp[i][j-1][w - nums[i]]+nums[i], dp[i-1][j][w])
// w 为元素和， j 


int main(){
    int n,sum=0;
    cin >> n;
    vector<int> nums(n,0);
    vector<vector<int>> dp(n, vector<int>(n,0));

    for(int i=0;i<n;i++){
        cin>>nums[i];
        sum+=nums[i];
    }
    int target_sum = sum/2; //所求和的目标值
    int target_n = (n+1)/2; //所分数组的目标数量

    for(int i=0;i<n;i++){
        for(int j=0;j<target_n;j++){

        }
    }




}