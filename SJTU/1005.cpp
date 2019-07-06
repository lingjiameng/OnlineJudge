#include <iostream>
#include <map>
using namespace std;


int n;
map<int,int> cnt;
int board[9][9];

bool check()
{
    for(int i=0;i<9;i++){
        cnt.clear();
        for(int j=0;j<9;j++){
            cnt[board[i][j]]++;
            //cout<<cnt[board[i][j]]<<endl;
            if(cnt[board[i][j]] > 1)return false;
        }
    }
    for(int i=0;i<9;i++){
        cnt.clear();
        for(int j=0;j<9;j++){
            cnt[board[j][i]]++;
            //cout<<cnt[board[j][i]]<<endl;
            if(cnt[board[j][i]] > 1)return false;
        }
    }
    for(int i=0;i<9;i+=3){
        for(int j=0;j<9;j+=3){
            cnt.clear();
            for(int m=i;m<i+3;m++){
                for(int n=j;n<j+3;n++){
                    cnt[board[m][n]]++;
                    //cout<<cnt[board[m][n]]<<endl;
                    if(cnt[board[m][n]] > 1)return false;
                }
            }
        }
    }
    return true;
}



int main()
{

    cin>>n;
    bool res[n];
    
    //main load loop
    for(int l=0;l<n;l++){
        //read
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cin>>board[i][j];
            }
        }
        cnt.clear();
        res[l]=check();
        cnt.clear();
    }
    //cout<<res[0]<<endl;
    for(int i=0;i<n;i++){
        if(res[i])cout<<"Right"<<endl;
        else cout<<"Wrong"<<endl;
    }
    return 0;
}