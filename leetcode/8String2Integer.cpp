#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

int myAtoi(string str)
{
    int res = 0, sign = 1, length = str.size();
    bool iend = false,tag=true;
    int b = INT32_MAX/10;
    for(int i=0; i<length ; i++){
        if(tag && str[i]=='-'){
            sign=-1;
            tag=false;
        }
        else if (tag && str[i] == '+')
        {
            sign = 1;
            tag = false;
        } else if(str[i]>='0' && str[i]<='9')
        {
            tag = false;
            int delta = str[i] - '0';
            if(sign==1 && (res > b || (res==b && delta >= 7)))return INT32_MAX;
            if(sign==-1 && (res > b || (res==b && delta >= 8)))return INT32_MIN;
            res = res*10 + delta;
        }
        else if (!tag || str[i]!=' ')//之前可以为空格，出现数字后不可以
            break;
    }
    res = sign * res;
    return res;
}



int main()
{
    cout << myAtoi(" -a987 sdf") << endl;
    return 0;
}