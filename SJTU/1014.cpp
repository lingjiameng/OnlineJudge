#include <iostream>

//高精度加法

using namespace std;

//假设求和的为两个正整数
string lint_add(const string &num1, const string &num2){
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

int main()
{
    // string num1 = "-11133";
    // string num2 = "123456";
    string num1,num2;
    cin>>num1>>num2;
    string res = lint_add(num1,num2);
    cout<<res<<endl;
    return 0;
}