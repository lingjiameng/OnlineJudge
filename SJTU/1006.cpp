#include <iostream>
#include <limits.h>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int temp,temp2;
    cin>>temp2>>temp;
    int sum=temp2+temp,tail=temp2+temp;
    for(int i=2;i<n;i++){
        temp2=temp;
        cin>>temp;
        tail=max(tail,temp2)+temp;
        sum=max(tail,sum);
    }
    if(sum>0)cout<<sum;
    else cout<<"Game Over";
    
    return 0;
}

/*
int main()
{
    int n;
    cin>>n;
    int temp;
    cin>>temp;
    int sum=temp,tail=temp;
    for(int i=1;i<n;i+c+){
        cin>>temp;
        tail=max(tail+temp,temp);
        sum=max(tail,sum);
    }
    if(sum>=0)cout<<sum;
    else cout<<"Game Over";
    
    return 0;
}
//对子列长度无要求的解法，本题要求子列长度大于二
*/