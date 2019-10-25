#include<iostream>
#include<string>
#include <vector>
#include <queue>

using namespace std;

class Plane{
    public:
    int id,t,u,g;
    Plane(int nid,int t1,int u1,int g1):id(nid),t(t1),u(u1),g(g1){};
};

struct comp{
    bool operator()(const Plane & p1,const Plane &p2){ 
        return p1.t > p2.t;
    }
};

struct compId{
    bool operator()(const Plane&p1,const Plane&p2){
        return p1.id > p2.id;
    }
};

int main(){
    int N, Max, S;
    cin >>N >>Max >>S;
    priority_queue<Plane,vector<Plane>,comp> planeQueue;
    int landTime = 0;
    int * landTimes = new int [N];

    int t, u, g;

    for(int i=0;i<N;i++){
        cin >>t >>u >>g;
        planeQueue.push( Plane(i,t,u,g) );
    }

    int first=1;
    while (!planeQueue.empty() && planeQueue.top().t < Max)
    {
        // 去除当前到达的飞机 tPlane
        const Plane &tp = planeQueue.top();
        Plane tPlane(tp.id,tp.t,tp.u,tp.g);
        planeQueue.pop();
        // cout << tPlane.t <<" | "<<tPlane.u<<" | " <<tPlane.g;
        //检查crash
        if (!planeQueue.empty() && tPlane.t == planeQueue.top().t)
        {
            cout << "CHANGE BOYFRIEND" << endl;
            return 0;
        }

        if(!first && tPlane.t + tPlane.u < landTime+S){
            //不能安全降落 => refly;
            Plane rPlane(tPlane.id,tPlane.t + tPlane.g, tPlane.u, tPlane.g);
            planeQueue.push(rPlane);
            // cout << " >>> refly "<< rPlane.t << endl;
        }else{
            //安全 => land
            landTime = (tPlane.t + tPlane.u);
            landTimes[tPlane.id] = landTime;
            // cout << " >>> land "<< landTime << endl;
        }
        first = 0;
    }

    if (!planeQueue.empty() || landTime > Max){
        cout << "GO DATING" << endl;
    }else{
        for (int i = 0; i < N; i++){
            cout << landTimes[i] << endl;
        }
    }
    delete [] landTimes;
    return 0;
}