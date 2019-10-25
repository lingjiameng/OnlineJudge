#include <iostream>
#include <vector>
#include <time.h>
#include <string.h>
using namespace std;

// int N = 2147483647;
int N = 200;
//快速质数筛选
//质数：因数只有1和它本身的正整数（不包括1）
//方法:sieve of Eratosthenes 简称埃氏筛，也称素数筛
//实际使用方法二即可，简单而且很快，不需要特殊优化

//找出从2到N之间所有的质数

vector<int> method1(){
    //遍历，利用定义判断每个数是否为质数
    //暴力算法
    int i,j;
    vector<int> primes;
    for(i=2; i<=N ;i++){
        for(j=2;j<i ;j++){
            if(i%j==0)break;
        }
        if(j < i)continue;
        primes.push_back(i);
    }
    return primes;
}

//实际使用方法二即可，简单而且很快，不需要特殊优化
vector<int> method2(){
    //遍历，删除所有素数的倍数，因为合数一定可以分解为素数的乘积
    //优点: 速度快
    //缺点: 占用内存多
    vector<int> primes;
    bool is_prime[N]; //int i == is_prime[i-1]
    memset(is_prime,1,N);

    is_prime[0]=false;
    for(int i = 2 ; i < N ;i++){
        primes.push_back(i);
        for (int j = 2; i * j <= N; j++) 
            is_prime[i*j-1]=false;
        while (!is_prime[i])i++;
    }
    return primes;
}

vector<int> method3()
{
    //对方法2的进一步优化，因为方法二会重复删除
    //优化：
    //   跳过偶数
    //   只记录奇数节省内存
    //   j 从 i*i开始，避免重复筛选
    vector<int> primes;
    bool is_prime[N/2 +1]; //int i == is_prime[(i-1)/2]只记录奇数
    memset(is_prime, 1, N/2+1);

    if(N>=2)primes.push_back(2);
    is_prime[0] = false;
    for (int i = 3; i <= N; i+=2)
    {
        primes.push_back(i);
        if(i < N/i){ //避免 i*i 越界
            for (int j = i * i; j <= N; j += 2*i) //注意加2*i
                is_prime[j / 2] = false;
        }
        while (!is_prime[i/2+1])i+=2;
    }
    return primes;
}
//乘法注意整数越界



void print(const vector<int> & v){
    //输出
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    cout << endl;
}

int main(){
    // auto t0 = clock();
    // auto primes = method1();
    // cout<< (clock()-t0) * 1.0/CLOCKS_PER_SEC << endl;
    // // print(primes);

    auto t0 = clock();
    auto primes = method2();
    cout << (clock() - t0) * 1.0 / CLOCKS_PER_SEC << endl;
    print(primes);

    t0 = clock();
    primes = method3();
    cout << (clock() - t0) * 1.0 / CLOCKS_PER_SEC << endl;
    print(primes);

    return 0;
}