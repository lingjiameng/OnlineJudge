#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

/*
双指针，从两端遍历
将两个板之中较板的板向中间移动
逐步比较结果
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int hLength = height.size();    
        int l=0, r = hLength-1;
        int maxVolume = 0;

        while( l < r ){
            maxVolume = max(maxVolume,min(height[l],height[r])*(r-l));
            if(height[l]>height[r])r--;
            else l++;
        }
        return maxVolume;
    }
};

int main(){
    int input [] = {1,8,6,2,5,4,8,3,7};
    vector<int> height(input,input+(sizeof(input)/sizeof(int)));
    Solution mySol;
    cout << mySol.maxArea(height)<<endl;
    return 0;
}