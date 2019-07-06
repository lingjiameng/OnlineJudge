#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int reverse(int x)
{
    // tips: INT32 -2147483648 to 2147483647
    // suppose x = [i1,i2,i3,...,ik], 0 <= ik <= 9
    // overflow happens only when
    // reverse([i2,i3,...,ik]) > INT32_MAX/10 or reverse([i2,i3,...,ik]) < -1*INT32_MAX/10
    // if they are equal, then i1 need to be -8 <= i1 <=7
    // but (-8 <= i1 <=7) is't necessary
    // since when they are equal, i1 must <=2,(X is INT32) 
    int ans = 0;
    int b = INT32_MAX / 10;
    while (x != 0)
    { // only need to check the ans part
        if (ans < -b || ans > b)
            return 0;
        ans = ans * 10 + x % 10;
        x = x / 10;
    }
    return ans;
}

int main()
{
    
    cout<<reverse(555)<<endl;
    return 0;
}