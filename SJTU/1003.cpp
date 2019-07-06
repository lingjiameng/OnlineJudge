#include <iostream>

using namespace std;

void check_fill(int** arr,short l,short i,short j)
{
    if(i>0&&arr[i-1][j]==0){
        arr[i-1][j]=3;
    }
    if(j>0&&arr[i][j-1]==0){
        arr[i][j-1]=3;
    }
    if(i<l-1&&arr[i+1][j]==0){
        arr[i+1][j]=3;
    }
    if(j<l-1&&arr[i][j+1]==0){
        arr[i][j+1]=3;
    }
}

bool full( int** arr,short l){
    for(int i=0;i<l;i++){
        for(int j=0;j<l;j++){
            if(arr[i][j]==0)return 0;
        }
    }
    return 1;
}


int main()
{
    short l;
    cin>>l;
    //建立动态数组
    int *board[l];
    for(int i=0;i<l;i++){
        board[i]=new int[l];
    }
    //

    for(int i=0;i<l;i++){
        for(int j=0;j<l;j++){
            cin>>board[i][j];
        }
    }
    int cnt=0;
    while(!full(board,l)){
        for(int i=0;i<l;i++){
            for(int j=0;j<l;j++){
                if(board[i][j]==1)check_fill(board,l,i,j);  
            }
        }
        for(int i=0;i<l;i++){
            for(int j=0;j<l;j++){
                if(board[i][j]==3)board[i][j]=1;
            }
        }
        cnt++;
    }
    cout<<cnt;

    //建立动态数组
    for(int i=0;i<l;i++){
        delete [] board[i];
    }
    //

    return 0;
}