#include <iomanip>
#include <iostream>

using namespace std;
//根据边长输出环形山

int main()
{
    int n, max_n, step, mountain[150][150];
    cin >> n;
    max_n = n * n;

    step = 0;
    for (int i = 0; step < max_n; i++)
    {   //按回字形路径填充数字
        int j = i, k = i;
        if (step == max_n - 1) //解决奇数的终止条件问题
            mountain[j][k] = ++step;
        for (;j < n - i -1; j++)mountain[j][k] = ++step;
        for (;k < n - i - 1; k++)mountain[j][k] = ++step;
        for (;j > i; j--) mountain[j][k] = ++step;
        for (;k > i; k--)mountain[j][k] = ++step;
    }
    //输出
    for(int i=0; i < n; i++){
        for (int j = 0; j < n; j++)
            cout << setw(6) << mountain[j][i];
        cout << endl;
    }
}