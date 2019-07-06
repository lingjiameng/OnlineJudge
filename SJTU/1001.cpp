#include <iostream>
using namespace std;

int main()
{
    short ho2,hod,num,hoa,count=0;
    cin>>ho2>>hod>>num;
    for(int i=0;i<num;i++){
        cin>>hoa;
        if(hoa<=(ho2+hod))count++;
    }
    cout<<count<<endl;
    return 0;
}
