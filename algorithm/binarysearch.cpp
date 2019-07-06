#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int binarySearch(vector<int> & nums, int target){
    int start = 0, end = nums.size() - 1;
    int mid=0;
    cout << "***search begin!***"<<endl;
    while(true){
        
        mid = start + ( end - start )/2;  //直接相加求和可能会溢出
        cout << "left: " << start << " right: " << end <<" index: "<< mid << endl;
        if(start > end) {
            mid = -1;
            break;
        }
        
        if(nums[mid]==target)
            break;
        if(nums[mid] < target)
            start = mid+1;
        else
            end = mid-1;
    }
    
    if (mid == -1) 
        cout << "[ target not found! ]" << endl;
    else
        cout<< "[ index: "<< mid+1<< " ]"<<endl;

    cout<< "***search end!***" <<endl;
    return mid;
} 



int main()
{
    vector<int> nums = {1,2,3,4,5,8};
    int target;
    while(true){
        cout<< "=================\nenter your target:";
        cin >> target;
        binarySearch(nums, target);
    }
    return 0;
}