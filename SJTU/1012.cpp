#include <iostream>

using namespace std;

/*
note: 动态规划,增长率应为0<x<=1
更新当前节点的可能下一个节点时，长度和**长度计数**应该基于前一个节点更新
*/

int main()
{
    int S,T;
    cin>>S>>T;
    long long int length[200020]={0};
    long long int cnt[200020]={0};

    //初始化
    for(long long int i=0;i<200020;i++)
    {
        length[i]=1;
        cnt[i]=1;
    }

    long long int tmp=0,maxlength=0,lengthcnt=0;

    //计算,i to next
    for(long long int i=S;i<=T;i++)
    {
        for(int j=1;j<=100;j++)
        {
            if((i*j)%100==0)
            {
                //cout<<tmp<<endl;
                tmp=(i*j)/100+i;//cal next index possible
                //cout<<"tmp"<<tmp<<endl;
                if(tmp>T)
                {
                    //cout<<"i: "<<i<<"   j: "<<j<<endl;
                    break;
                }
                else
                {
                    if((length[i] + 1) == length[tmp])
                    {
                        //两部分次数叠加,i tmp 处次数叠加
                        cnt[tmp]+=cnt[i];
                    }
                    else if ((length[i] + 1 )> length[tmp])
                    {
                        //tmp次数更新为i处次数
                        cnt[tmp]=cnt[i];
                        length[tmp] = length[i] + 1;
                    }
            
                }
            }
        }
        if (length[i] > maxlength)
        {
            maxlength = length[i];
            lengthcnt = cnt[i];
        }
        else
        {
            if (length[i] == maxlength)
                lengthcnt += cnt[i];
        }
    }  
    cout<<maxlength<<"\n"<<lengthcnt<<endl;
    return 0;
}