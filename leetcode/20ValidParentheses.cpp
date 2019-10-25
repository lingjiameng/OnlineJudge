#include <iostream>

using namespace std;

class Solution{
    public:
    bool isValid(string s){
        // char * stack = new char[s.size()]; //析构不好写
        char stack[s.size()];
        int tail = 0;
        for(char c:s){
            if(c == '[' || c=='(' || c=='{'){//入栈
                stack[tail++] = c;
            }else{ //出栈
                if(tail <= 0 ) return false; //右括号多于左括号
                if(c - stack[--tail] != 2 && c - stack[tail] !=1)return false;//括号类型不匹配
            }
        }
        if(tail != 0) return false;
        return true;
    }
};

int main(){
    Solution mySol;
    while(1){
        string text;
        cin >>text;
        cout << "[isValid]" <<mySol.isValid(text)<<endl;
    }
    return 0;
}