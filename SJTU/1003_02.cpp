#include <stdio.h>
#define N 105
//using namespace std;

const int d[][2]={{-1,0},{0,-1},{1,0},{0,1}};

int b[N][N];

int x[N*N],y[N*N],top=0;
int s[N*N],t[N*N],cnt=0;

int m=0;

int main(){
    int l;
    //cin >>l;
    scanf("%d",&l);
    for(int i=0;i<l;i++){
        for(int j=0;j<l;j++){
            //cin>>b[i][j];
            scanf("%d",&b[i][j]);
            if(b[i][j]==1){
                x[top]=i;
                y[top]=j;
                top++;
            }

        }
    }
    while(1){
        cnt=0;
        for(int k=0;k<top;k++){
            for(int i=0;i<4;i++){
                int nx=x[k]+d[i][0];
                int ny=y[k]+d[i][1];
                if(nx<0||ny<0||nx>=l||ny>=l)continue;
                if(b[nx][ny]==0){
                    b[nx][ny]=1;
                    s[cnt]=nx;
                    t[cnt]=ny;
                    cnt++;
                }
            }
        }
        if(cnt==0)break;
        m++;
        top=cnt;
        for(int i=0;i<cnt;i++){
            x[i]=s[i];
            y[i]=t[i];
        }
    }
    //cout<<m;
    printf("%d",m);
    return 0;
}