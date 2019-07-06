#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindrome(int x)
{
    if (x < 0)
        return false;
    int res = 0, tmp = x, b = INT32_MAX / 10;
    while (x != 0)
    {
        if (res > b)
            return false;
        res = res * 10 + x % 10;
        x = x / 10;
    }
    return res == tmp;
}

int main()
{
    cout<<isPalindrome(214564132)<<endl;
    return 0;
}