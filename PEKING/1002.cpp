#include <iostream>
#include <map>
#include <iomanip>
#include <time.h>

using namespace std;

//主要问题
//电话号码的存储,查找与计数 hard
//电话号码的格式转换 easy

int char2int(char c){
    if(c == '-') return -1;
    if( c >= '0' && c <= '9' ) return c-'0';
    if( c >= 'A' && c <= 'P' ) return (c-'A')/3 + 2 ;
    if( c >= 'R' && c <= 'Y' ) return (c-'Q')/3 + 7 ;
    return -1;
}

int main(){
    map<int,int> phonenums;
    ios::sync_with_stdio(false);
    // int phonenums[MAXSIZE] = {0};
    char buf[20];
    int num,phonenum;

    cin >> num;
    for(int i=0;i<num;i++){
        cin >> buf;
        // cout <<"buf " <<buf<<endl;
        phonenum = 0;
        for(int i = 0; buf[i]!='\0' ; i++){
            if( buf[i] != '-' )
                phonenum = phonenum * 10 + char2int(buf[i]);
        }
        // cout <<"trans " <<phonenum << endl;
        phonenums[phonenum] = phonenums[phonenum]+1;
    }

    int flag = 0;
    for(map<int,int>::iterator it = phonenums.begin();it !=phonenums.end() ; ++it ){
        if( it->second > 1 )
        {
            cout << setfill('0') << setw(3) << it->first / 10000 << '-' << setfill('0') << setw(4)<< it->first % 10000 << ' ' << it->second << endl;
            flag = 1;
        }
    }
    if(flag == 0)
        cout<<"No duplicates."<<endl;

    return 0;
}