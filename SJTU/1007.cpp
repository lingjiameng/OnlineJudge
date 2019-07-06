#include <iostream>
#include <string>

using namespace std;

int main()
{
    string num1,num2,res="";
    cin>>num1>>num2;
    int l1=num1.size(),l2=num2.size(),i,t=0;
    for(i=0;i<l1&&i<l2;i++){
        if(i==2){
            res="."+res;
            continue;
        }
        t+=(num1[l1-i-1]-'0')+(num2[l2-i-1]-'0');
        res=(char)(48+t%10)+res;
        t/=10;
    }
    for(;i<l1;i++){
        t+=(num1[l1-i-1]-'0');
        res=(char)(48+t%10)+res;
        t/=10;
    }
    for(;i<l2;i++){
        t+=(num2[l2-i-1]-'0');
        res=(char)(48+t%10)+res;
        t/=10;
    }
    if(t)res=(char)(48+t)+res;
    cout<<res;
    return 0;
}