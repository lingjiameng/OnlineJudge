#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

/*
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/

class Solution
{
public:
    string intToRoman(int num)
    {
        int index = 6;
        int value[] = {1,5,10,50,100,500,1000};
        char symbol[] = {'I','V','X','L','C','D','M'};
        int coefficient[7] = {0};

        int remainder=num % 4000;
        while(remainder != 0){
            coefficient[index] = remainder/value[index];
            remainder = remainder % value[index--];
        }
        string ans = "";

        index ++;
        while(index < 6){
            if (0 == index % 2 && 4 == coefficient[index])
            { //特殊情况  1,10,100的系数为4(下标对应0,2,4)
                if(0==coefficient[index+1]){ //5,50,500的系数为0或者1 分两种情况进行合并
                    ans = symbol[index]+(symbol[index+1] + ans); 
                }
                else{
                    ans = symbol[index] + (symbol[index + 2] + ans); 
                }
                index += 2;
                //结束后， 1,5，或者10,50 etc的数字全部转化完毕
            }else
            {      
                for (int i = 0; i < coefficient[index]; i++)
                {
                    ans = symbol[index] + ans;
                }
                index++;
            }
        }
        for (int i = 0; i < coefficient[index]; i++)
        {
            ans = symbol[index] + ans;
        }
        return ans;
    }
};



class Solution2
{
public:
    string intToRoman(int num)
    {
        int index = 6;
        int value[] = {1, 5, 10, 50, 100, 500, 1000};
        string symbol[] = {"I", "V", "X", "L", "C", "D", "M"};
        int factor[7] = {0};
        int remainder = num % 4000;
        
        while (remainder != 0)
        {
            factor[index] = remainder / value[index];
            remainder = remainder % value[index--];
        }
        string ans = "";

        index++;
        while (index < 7)
        {
            if (0 == index % 2 && 4 == factor[index])
            {
                ans = symbol[index] + (symbol[index + 1 + factor[index +1] ] + ans);
                index += 2;
            }
            else
            {
                for (int i = 0; i < factor[index]; i++)
                    ans = symbol[index] + ans;
                index++;
            }
        }
        return ans;
    }
};

int main()
{
    Solution2 mySol;
    cout<<"45"+string("45")<<endl;
    while(1){
        int num;
        cin >> num;
        cout << mySol.intToRoman(num) << endl;
    }
    
    return 0;
}