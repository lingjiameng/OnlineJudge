#include <iostream>
using namespace std;
//括号匹配

int main(){
    int N;
    char buf[110];
    
    cin >> N; //输入括号的数目
    for(int i=0 ; i < N ;i++){
        cin >> buf;
        int left = 0;
        for(int i=0 ; buf[i]!='\0';i++){
            if(buf[i]=='(') left++;
            if(buf[i]==')') left--;
            if(left < 0) break;
        }
        if(left < 0 || left>0) cout<<"NO"<<endl;
        else cout<<"YES"<< endl;
    }
    return 0;
}
