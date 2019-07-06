#include <iostream>

using namespace std;

int main()
{
    int a=0;
    short l,w;
    cin>>l>>w;
    int p[l+1][w+1];

    for(int i=0;i<=l;i++){
        p[i][0]=0;
    }
    for(int i=0;i<=w;i++){
        p[0][i]=0;
    }
    for(int i=1;i<=l;i++){
        for(int j=1;j<=w;j++){
            cin>>a;
            p[i][j]=a+p[i-1][j]+p[i][j-1]-p[i-1][j-1];
        }
    }
    int b=0;
    cin>>a>>b;
    int sum=0,temp=0;
    for(int i=a;i<=l;i++){
        for(int j=b;j<=w;j++){
            temp=p[i][j]+p[i-a][j-b]-p[i-a][j]-p[i][j-b];
            if(temp>sum){
                sum=temp;
            }
        }
    }
    cout<<sum;
    return 0;

}
