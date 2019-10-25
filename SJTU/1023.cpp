#include<iostream>

using namespace std;

//矩阵翻转


int main(){
    int N,a,b,arr[600][600];
    cin >> N;
    while(0 < N--){
        cin>>a>>b;
        for(int i=0;i < a; i++){
            for(int j=0;j<a;j++){
                //翻转方式不同
                if(b == 0){
                    cin >> arr[i][a-j-1];
                }else if(b==1){
                    cin >> arr[a-i-1][j];
                }else{
                    cin >>arr[j][i];
                }
            }
        }
        for(int i=0;i<a;i++){
            for (int j = 0; j < a; j++)
                cout << arr[i][j]<<' ';
            cout<<endl;
        }
    }
    
    return 0;

}