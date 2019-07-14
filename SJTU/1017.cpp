#include <iostream>

using namespace std;
//二哥养兔子

int main(){
    long long int a,b,c,N;
    cin >>a >>b>>c>>N;
    long long int m1,m2,m3,total,inc;
    m1 = 1 ;
    m2 = m3 = total = inc = 0;
    
    for(int i=1;i<=N;i++){ //第i个月
        inc = m1*a; //出生一个月的生出的兔子数
        inc += m2*b;
        inc += m3*c;
        m3 += m2;
        m2 = m1;
        m1 = inc;
    }
    cout << m1+m2+m3 << endl;


    return 0;
}