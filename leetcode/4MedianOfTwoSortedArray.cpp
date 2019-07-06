#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// O(n) solution，依次比较，得到最终输出。
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    int nums1Length = nums1.size();
    int nums2Length = nums2.size();
    int index1 = 0;
    int index2 = 0;
    int even = (nums1Length + nums2Length + 1) % 2; //is even?
    int indexMedian = (nums1Length + nums2Length + 1) / 2;
    double medians[2] = {0.0,0.0};
    while(1)
    {
        if (index1< nums1Length && (index2 >= nums2Length || nums1[index1] < nums2[index2]))
        {
            // 数列一没有搜索完，并且（数列二搜索完了 或者 数列一比数列二的末尾数值小）
            //那么数列一的指针指向的值，是所有未搜索数中最小的。即是应排好序的下一个值。
            medians[0] = medians[1];
            medians[1] = nums1[index1++]; 
        }
        else if (index2 < nums2Length && (index1 >= nums1Length || nums1[index1] >= nums2[index2]))
        {
            medians[0] = medians[1];
            medians[1] = nums2[index2++];
        }
        //注意上面的下标都指向的是已排好序的数字的后面一位
        // cout << medians[0] << " " << medians[1]<< " "<< index1<<" "<<index2 << endl;
        if (!even && index1+index2 == indexMedian){
            return medians[1];
        }
        if(even && index1+index2-1 == indexMedian)
        {
            return (medians[1]+medians[0])/2.0;
        }
        // if(index1 >= nums1Length && index2 >= nums2Length){
        //     break;
        // }
    }
    return -1;
}

//O(logn) solution，二分搜索查找临界值即可
double findMedianSortedArrays_Ologn(vector<int> & nums1, vector<int> & nums2){
    if (nums1.size() > nums2.size())
        swap(nums1, nums2);
    int mid1=0,mid2=0;
    int Length1 = nums1.size();
    int Length2 = nums2.size();
    int i_sum = (Length1 + Length2 + 1) / 2;
    int even = (Length1 + Length2 + 1) % 2;
    
    //特殊情况，一个数组为空的的情况
    if(Length1 == 0){
        if (even){
            return double(nums2[i_sum-1]+nums2[i_sum])/2.0;
        }else{
            return nums2[i_sum-1];
        }
    }

    // mid1+mid2 = i_sum;

    //binary search begin
    int start = 0, end = Length1;
    int token = 0;
    while(true){
        mid1 = start + (end - start + 1) / 2;
        mid2 = i_sum - mid1;
        if (start  >  end) break; //找不到中位数的情况，实际不会发生


        cout << "mid1: " << mid1 << " mid2: " << mid2 << " i_sum " << i_sum << endl;

        token = 0 + int(mid1 == 0 || mid2 == Length2 || nums1[mid1 - 1] <= nums2[mid2]); // A[i-1]< B[j]
        token += 2 * int(mid1 == Length1 || mid2 == 0 || nums1[mid1] >= nums2[mid2 - 1]); // A[i] > B[j-1]
        // cout<<token<<endl;
        if(token == 3) 
            break;
        if(token == 1)
            start = mid1+1;
        if(token == 2)
            end = mid1-1;

    }

    cout << "====res===\nmid1: "<< mid1<<" mid2: "<< mid2 <<" i_sum "<<i_sum<< endl;
    double rtn[2] = {0.0,0.0};

    if(mid1 == 0){
        rtn[0] = nums2[mid2-1];
    }else if(mid2 == 0){
        rtn[0] = nums1[mid1-1];
    }else{
        rtn[0] = max(nums1[mid1-1],nums2[mid2-1]);
    }

    if (mid1 == Length1)
    {
        rtn[1] = nums2[mid2];
    }
    else if (mid2 == Length2)
    {
        rtn[1] = nums1[mid1];
    }
    else
    {
        rtn[1] = min(nums1[mid1], nums2[mid2]);
    }

    if(even) return (rtn[0]+rtn[1])/2.0;
    return rtn[0];
}
//O(logn) solution
double findMedianSortedArrays_Ologn_beta(vector<int> &nums1, vector<int> &nums2){
    if (nums1.size() > nums2.size())
        swap(nums1, nums2); // make sure nums1 is the shorter one.
    int Length1 = nums1.size();
    int Length2 = nums2.size();

    int start = 0, end = Length1, iSum = (Length1 + Length2 + 1)/2; 
    while(start <= end){
        int mid1 = start + (end - start + 1)/2; //no overflow
        int mid2 = iSum - mid1;
        if(mid1 > start && nums1[mid1-1] > nums2[mid2]){
            // mid1 is too big, need to move left
            // mid1 > start ==> mid2 < Length2 
            end = mid1 - 1;
        }else if(mid1 < end && nums1[mid1] < nums2[mid2-1]){
            // mid1 is too small, need to move right
            // mid1 < end ==> mid2 > 0
            start = mid1 + 1;
        }else{ //mid1 is perfect
            // [Attention!!]:odd first,for case Length1=0,Length2=1
            int maxLeft = 0;
            if(mid1 == 0){maxLeft = nums2[mid2-1];}
            else if (mid2 == 0){maxLeft = nums1[mid1-1];}
            else{maxLeft = max(nums1[mid1-1],nums2[mid2-1]);}
            if((Length1 + Length2)%2 == 1) return maxLeft;

            int minRight = 0;
            if(mid1 == Length1){minRight = nums2[mid2];}
            else if(mid2 == Length2){minRight = nums1[mid1];}
            else{minRight = min(nums1[mid1],nums2[mid2]);}
            return (maxLeft + minRight)/2.0;
        }
    }
    return 0.0;
}
/*
虽然使用了Olog(n)算法但是实际上和O(n)算法运行时间相差无几；
更有趣的是最快的实际算法，复杂度应该是O(n)的
*/
int main()
{
    vector<int> nums1={};
    vector<int> nums2={2};
    cout<<findMedianSortedArrays_Ologn_beta(nums1,nums2)<<endl;
    // int n;
    // cin>>n;
    return 0;
}