#include <iostream>
#include <string>

using namespace std;


//data used to calculate weekday
int leap_mouthArr[]={0,5,1,2,5,0,3,5,1,4,6,2,4};//leap year
int comm_mouthArr[]={0,6,2,2,5,0,3,5,1,4,6,2,4};//common year

//
int weekvalue(int d,int m,int y)
{
    int mcode;
    if((y%100!=0 && y%4==0)||y%400==0){
        mcode=leap_mouthArr[m];
    }
    else{
        mcode=comm_mouthArr[m];
    }
    y=y%100;
    int wcode=(d+mcode+(y/4+y)%7)%7;
    return wcode;
    //0->sunday,1-6 -> Mon-Sat
}
//same year
//dif of year = 1
//no weekend 1.1 5.1-5.3 10.1-10.7
//dif of year greater than 1

int count(string date1,string date2)
{
    int d1, m1, y1, d2, m2, y2;
   
    //
}


int main()
{
    int n;
    string date1,date2;
    int res[n];
    for(int i=0;i<n;i++){
        cin>>date1>>date2;
        res[i]=count(date1,date2);
    }
    for(int i=0;i<n;i++){
        cout<<res[i]<<endl;
    }
    //cout<<weekvalue(19,11,2017);
    return 0;
}