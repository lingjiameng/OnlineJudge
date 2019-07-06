#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

bool canThreePartsEqualSum(vector<int> &A)
{
    int length = A.size();
    vector<int> sum(length, A[0]);
    for (int i = 1; i < length; ++i)
    {
        sum[i] = sum[i - 1] + A[i];
    }
    int localSum = sum[length - 1] / 3.0;
    int cnt = 1;
    for (int i = 0; i < length; ++i)
    {
        if (sum[i] == localSum * cnt)
        {
            cnt++;
            if (cnt == 4)
                return true;
        }
    }
    return false;
}

int main(){
    
    return 0;
}

