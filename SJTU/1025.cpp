#include <iostream>
using namespace std;

//消防车灭火
//区间求并集的区间长度

void quick_sort(int *nums,int left,int right,int *nums2){
    if(left>=right)return;
    int l = left,r = right;
    int key = nums[l++];
    while(l<r){
        while(l<r && nums[r]> key) r--;
        while(l<r && nums[l]<=key) l++;
        swap(nums[l],nums[r]);
        swap(nums2[l],nums2[r]);
    }
    if(nums[l] <= nums[left]) {
        swap(nums[left],nums[l]);
        swap(nums2[left], nums2[l]);
    }else l--;

    quick_sort(nums,left,l-1,nums2);
    quick_sort(nums,l+1,right,nums2);
}

int main()
{
    int N,len, left[20010], right[20010]; //原始数据
    cin >> N;
    for(int i=0;i<N;i++)
        cin  >> left[i] >> right[i];
    //排序
    quick_sort(left,0,N-1,right);
    len = 0;
    int r;
    for(int i = 0 ; i < N ;i++){
        len -= left[i]; //减去左边界
        r = right[i];
        while(i < N - 1 && r >= left[i+1])
            r = max(right[++i],r); //找到连续的最右边界
        len += r; //加上最右边界
    }
    cout << len <<endl;
    return 0;
}