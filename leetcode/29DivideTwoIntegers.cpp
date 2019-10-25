#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        bool sign = true; //true if result positive else negtive
        if (dividend > 0)
        {
            dividend = -dividend;
            sign = !sign;
        }
        if (divisor > 0)
        {
            divisor = -divisor;
            sign = !sign;
        }

        int res = 0;
        while (dividend <= divisor)
        {
            int x = divisor;
            int i = 0;
            // 2^(i+1)*divisor < dividend <= 2^(i)*divisor;
            while (true)
            {
                if (x < -(1 << 30))
                    break;
                if (dividend > x + x)
                    break;
                x = x + x;
                i++;
            }
            res += 1 << (i); //when i == 31,it's to negtive;
            dividend -= x;
        }
        if (res == INT_MIN)
            return sign ? INT_MAX : INT_MIN;
        return sign ? res : -res;
    }
};



class Solution_dp(){
    int divide(int dividend,int divisor){
        //both trans to negtive, avoid exceed;
        bool sign = true;
        if(dividend> 0){
            dividend = -dividend;
            sign = !sign;
        }
        if(divisor >0){
            divisor = -divisor;
            sign = !sign;
        }

        int nums[32];
        int size = 0;
        nums[size++] = divisor;
        while(divisor > -(1<<30) && divisor+ divisor > dividend){
            nums[size++] = divisor = divisor + divisor;
        }//生成所有可能中间值

        int res=0;
        while(dividend < 0 && size >0){ //当被除数没有除尽时
            if (dividend <= nums[size - 1]){ //可以除就除
                dividend -= nums[size-1]; //
                res -= 1<<(size-1);
            }else size--; //否则递减
        }
        if(res == INT_MIN) return sign?INT_MAX:INT_MIN;
        return sign?-res:res;


    }
}