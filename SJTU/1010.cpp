#include <iostream>

using namespace std;

int main(){
    int arr[12];
    int remainder=0,diff=0,sum=0;
    
    for(int i=0;i<12;i++){
        cin>>arr[i];
    }
    
    for(int i=0;i<12;i++){
       diff=300+remainder-arr[i];
       if(diff<0){
           cout<<(-1-i)<<endl;
           return 0;
       }
       sum+=diff/100;
       remainder=diff%100;
    }
    cout<<int(sum*120)+remainder<<endl;
    return 0;
}
