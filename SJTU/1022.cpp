#include <iostream>

using namespace std;

//求解 fibonacci数列 mod 2010

//递推方案太慢 只能解决 80%
void recurrence(){
    long long N;
    cin >> N;

    int a1 = 0, a2 = 1;
    int an = 1;
    for (long long i = 1; i < N; i++)
    {
        an = (a1 + a2) % 2010;
        a1 = a2;
        a2 = an;
    }
    cout << an << endl;
}

//使用fib矩阵递推式+矩阵快速幂
void times(int arr1[2][2],int arr2[2][2]){
    int tmp[2][2];
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            tmp[i][j] = arr1[i][0] * arr2[0][j] + arr1[i][1] * arr2[1][j];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            arr1[i][j] = tmp[i][j] % 2010;
}

int main(){
    long long N;
    cin >> N;

    int an = 1;

    //矩阵初始化
    int ans[2][2],pow[2][2];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++){
            ans[i][j] = (i==j); //单位阵
            pow[i][j] = !(i && j); //递推累乘的矩阵
        }

    //矩阵快速幂
    while(N>0){ //将N看做二进制数进行分解
        if(N&1)times(ans,pow); //如果当前最低位为1，需要累乘上当前幂
        times(pow, pow); //快速幂的累计累乘
        N=N/2; //将数N向右移位
    }

    // ans 乘以 [1, 0]^T 得到的结果 [a_N+1,a_N]^T
    an = ans[0][1]%2010;
    cout << an << endl;

    return 0;
}