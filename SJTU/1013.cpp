#include <iostream>
using namespace std;

//recursive solution
/*
int knap(int volume_knap,int *volume_things,int *value_things,int things_num)
{
    if(volume_knap<=0)return 0;
    int maxvalue=0,tmp_value;
    for(int i=0;i<things_num;i++)
    {
        int new_volume_knap = volume_knap -volume_things[i];
        if(new_volume_knap>=0 )
        {
            tmp_value=knap(new_volume_knap,volume_things,value_things,things_num)+value_things[i];
            if(tmp_value>maxvalue)maxvalue=tmp_value;
        }
        else
        {
            continue;
        }
    }

    return maxvalue;
}
*/


//traverse method
/*
int traverse(int volume_knap,int *volume_things,
                int *value_things,int kind_things)
{
    int maxvalue=0,tmpvalue=0,tmp_volume_used=0;
    for(int v1=volume_knap;v1>0;)
    {
        for (int v1 = volume_knap; v1 > 0;)
        {

        }
    }
}
*/


//dynamic method

//TODO: oj runtime error
int knap(int volume_knap, int *volume_things, int *value_things, int things_num)
{
    int values[10010];
    int tmpvalue=0,maxvalue=0;
    values[0]=0;
    for(int v=1;v<=volume_knap;v++)
    {
        //每个背包体积为v价值为values[v]

        maxvalue=values[v-1];
        for(int i=0;i<things_num;i++)
        {
            //volume_things
            if(v>=volume_things[i])
            {
                tmpvalue=values[v - volume_things[i]]+value_things[i];
                if(tmpvalue>maxvalue)
                {
                    maxvalue=tmpvalue;
                }
            }
        }
        values[v]=maxvalue;
    }
    //delete [] values;
    return maxvalue;
}


int main()
{
    int V,N;
    cin >>V>>N;
    
    if(V<=0){
        cout<<0<<endl;
        return 0;
    }
    int volumes [10010];
    int values_in[1010];
    for(int i=0;i<N;i++)
    {
        cin >> volumes[i] >> values_in[i];
    }

    cout << knap(V, volumes, values_in, N) << endl;
    //delete [] volumes;
    //delete [] values_in;
    return 0;
}