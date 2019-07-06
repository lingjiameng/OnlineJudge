#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


//visit by row, 
// time o(n)
// sapce o(n)
string convert(string s, int numRows)
{
    string rtn = "";
    int Length = s.size(),T = numRows - 1,Cycle = 2*T;
    if(T==0) return s;
    for(int line = 0 ; line <= T ; ++line){
        for (int k = 0; k - T < Length; k+=Cycle)
        {
            // cout<< "k : "<< k <<endl;
            int index = k - line;
            // cout << " index- : " << index;
            if (index >= 0 && index < Length) rtn += s[index];
            if(line!= 0 && line !=T){
                index = index + line + line;
                // cout << " index+ : " << index;
                if (index < Length)
                    rtn += s[index];
            }
            // cout<<endl;
        }
    }
    return rtn;
}

int main()
{
    string s = "PAYPALISHIRING";
    cout<<"input : "<< s <<endl;
    cout<<convert(s,5)<<endl;
    return 0;
}