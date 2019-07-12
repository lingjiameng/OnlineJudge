#include <iostream>
#include <vector>
#include <string>
#include <string.h>

//高精度乘法

using namespace std;

string lint_add(const string &num1, const string &num2)
{
    int s1 = (num1[0] == '-');
    int s2 = (num2[0] == '-');
    int i1 = 0, i2 = 0;
    string res = "";
    int carry = 0;

    for (; i1 < num1.size() - s1 && i2 < num2.size() - s2; i1++, i2++)
    {
        int sum = carry + (num1[num1.size() - i1 - 1] - '0') + (num2[num2.size() - i2 - 1] - '0');
        res = char('0' + (sum % 10)) + res;
        carry = sum / 10;
    }

    for (; i1 < num1.size() - s1; i1++)
    {
        int sum = carry + (num1[num1.size() - i1 - 1] - '0');
        res = char('0' + (sum % 10)) + res;
        carry = sum / 10;
    }
    for (; i2 < num2.size() - s2; i2++)
    {
        int sum = carry + (num2[num2.size() - i2 - 1] - '0');
        res = char('0' + (sum % 10)) + res;
        carry = sum / 10;
    }
    if (carry != 0)
    {
        res = char('0' + carry) + res;
    }
    return res;
}

string lint_quot(string & num1,string &num2){
    //如果其中任何一个数为 “0”
    if (strcmp(num1.c_str(), "0") == 0 || strcmp(num2.c_str(), "0") == 0)
    {
        return string("0");
    }

    //乘法结果首位不会为 “0”
    int i1, i2;
    int carry = 0, quotient = 0;
    int char2int = 0;
    string tmp = "";
    string res = "";
    vector<string> results(10, "");

    res = "";
    for (i1 = 0; i1 < num1.size(); i1++)
    {
        quotient = carry = 0;
        tmp = "";

        char2int = num1[num1.size() - i1 - 1] - '0';
        //在计算过的表里查找
        if (results[char2int].size() != 0)
        {
            //如果已经计算过，直接使用
            tmp = results[char2int] + string(i1, '0');
            res = lint_add(res, tmp);
        }
        else
        {
            //计算结果表里不存在，进行计算
            for (i2 = 0; i2 < num2.size(); i2++)
            {
                quotient = (num2[num2.size() - i2 - 1] - '0') * char2int + carry;
                carry = quotient / 10;
                tmp = char('0' + quotient % 10) + tmp;
            }
            if (carry != 0)
            {
                tmp = char('0' + carry) + tmp;
            }
            //计算完成
            results[char2int] = tmp;
            res = lint_add(res, tmp + string(i1, '0'));
        }
    }
    return res;
}


int main(){
    // string num1 = "123";
    // string num2 = "24";
    string num1,num2;
    cin >> num1 >> num2;
    string res = lint_quot(num1,num2);
    cout << res <<endl;
    return 0;
}