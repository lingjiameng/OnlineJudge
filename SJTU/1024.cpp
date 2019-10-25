#include <iostream>
using namespace std;

//非常巧妙的 quicksort 写法，遍历过程的顺序和终止条件的判断都很特别
void quick_sort(int *nums, int left,int right){
    if (left >= right)
        return;
    int l = left,r = right;
    int key = nums[l++];
    while (l < r){
        while (l < r && nums[r] > key) r--; //右侧找到小于等于中值的数
        while (l < r && nums[l] <= key)l++; //左侧找到大于中值的数
        swap(nums[l], nums[r]); //交换
    }
    if (nums[left] >= nums[l]) swap(nums[left], nums[l]); //左指针移动过，那么左指针的值一定小于等于中值
    else l--; //大于中值 则 左指针没有移动过，则正好符合顺序
    quick_sort(nums,left,l-1);
    quick_sort(nums,l+1,right);
}

void merge_sort(int * nums,int left,int right){
    //终止条件
    if(right-left <= 0)return;
    //分解为子问题
    int mid = (right-left)/2 + left;
    merge_sort(nums,left,mid);
    merge_sort(nums,mid+1,right);
    //归并
    int tmp[right-left+1],i=0;
    int l = left,r = mid+1;
    while(l<=mid && r <= right){
        if(nums[l]<=nums[r]){
            tmp[i++] = nums[l++];
        }else{
            tmp[i++] = nums[r++];
        }
    }
    while (l <= mid) tmp[i++] = nums[l++];
    while (r <= mid) tmp[i++] = nums[r++];
    //复制回数组
    while(--i >= 0)nums[left+i] = tmp[i];
}

int main(){
    int N,nums[10000];
    cin >>N;
    for(int i=0;i<N;i++){
        cin >>nums[i];
    }
    // quick_sort(nums,0,N-1);
    merge_sort(nums, 0, N - 1);
    for (int i = 0; i < N; i++)
    {
        cout << nums[i]<<' ';
    }
    cout <<endl;
}