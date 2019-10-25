#include <iostream>
#include <map>
#include <math.h>
#include <vector>
using namespace std;

//分解质因数

//快速质数筛选；sieve
//快速质数分解;1 - sqrt(N)

vector<int> sieve(int N)
{
    //快速质数筛选
    vector<int> primes = {2};
    vector<bool> is_prime(N/2+1,true); //int i == is_prime[i-1]
    
    is_prime[0] = false;
    for (int i = 3; i <= N; i += 2)
    {
        primes.push_back(i);
        if (i < N / i)
        { //避免 i*i 越界
            for (int j = i * i; j <= N; j += 2*i)
                is_prime[j / 2] = false;
        }
        while (!is_prime[i / 2 + 1])
            i += 2;
    }
    return primes;
}

int main(){
    int N, t;
    map<int,int> factor;
    
    cin >> N;
    t = N;
    int sqrt_n = (int)sqrt(t);
    auto primes = sieve(sqrt_n);
    int n_primes = primes.size();

    for (int i = 0; t != 1 && i < n_primes; i++)
    {
        if(t % primes[i] == 0)
        {
            t = t / primes[i];
            factor[primes[i]]++;
            i = -1;
        }
    }
    
    if(t != 1) factor[t]++ ;
    cout << N <<"=";
    for(auto it = factor.begin();it!=factor.end();it++){
        cout<<it->first<<'('<<it->second<<')';
    }
    cout<<endl;
    return 0;
}