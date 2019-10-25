#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

//本题并不符合最优子结构的情况
//1 高度差最小的路径并不一定包含高度差最小的路径
//2 和出发点，终点高度差最小也不符合情况
//3 

//简单的单源最短路径方法并不能解决本题，因为存在相同最大路径差，但是上下界不同的情况。


//采用删除点和判断联通的策略 不可行。。

// 二分搜索 + bfs ： 二分方法提前设置阈值，再用bfs判断该阈值下能否下山，不能则二分增大阈值，能则二分减小阈值



struct spot{
    int x;
    int y;
    spot(int a,int b):x(a),y(b){};
};


bool bfs(int low,int high,int n,int m[][110]){
    if( m[0][0] < low || m[0][0] > high ) return false;
    queue<spot> myque;
    bool v[110][110] = {0};
    myque.push(spot(0,0));
    int to_x[4] ={-1, +1, 0, 0};
    int to_y[4] ={0, 0, -1, +1}; 
    
    while(!myque.empty()){
        spot s(myque.front().x, myque.front().y);
        myque.pop();
        if(s.x== n-1 && s.y==n-1) return true;
        for(int i=0;i<4;i++){
            int x= s.x+to_x[i], y=s.y+to_y[i];
            if(x<0 || x>=n || y<0 || y>=n || v[x][y]) continue;
            if(m[x][y]>=low && m[x][y]<=high){
                v[x][y]=1;
                myque.push(spot(x,y));
            }
        }
    }
    return false;
}



int main(){
    int N;

    cin>>N;
    int mout[110][110];
    bool vis[110][110] = {0};

    int h_min = 120, h_max = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> mout[i][j];
            h_min = min(mout[i][j],h_min);
            h_max = max(mout[i][j],h_max);
        }
    }
    
    int d_h_max = h_max-h_min;
    int d_h_min = abs(mout[N-1][N-1] - mout[0][0]);
    
    while (d_h_max > d_h_min)
    {
        bool flag = false;
        int mid = (d_h_max + d_h_min)/2;
        for(int i=h_min;i <= h_max-mid;i++){
            // i的可能范围为 h_min -> (h_max-mid)不可能再大了
            if(bfs(i,i+mid,N,mout)){
                flag = true;
                break;
            }
        }
        if(flag){
            d_h_max = mid;
        }else{
            d_h_min = mid+1;
        }
        // cout << d_h_min << d_h_max << mid << endl;
    }
    cout << d_h_min <<endl;
    return 0;
}