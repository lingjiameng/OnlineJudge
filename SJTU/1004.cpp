#include <iostream>
using namespace std;

int main()
{
    int M,T;
    short U,F,D;
    cin>>M>>T>>U>>F>>D;
    int t=0,res=-1;
    char temp;
    for(int i=0;i<T;i++){
        cin>>temp;
        if(temp=='f')t+=(2*F);
        else t+=(U+D);
        if(t>M&&res==-1){
            res=i;
        }
    }
    cout<<res;
    return 0;
}

