#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


int main(){
    map<string, int> str2int = { {"begin",7}, {"end",8}, {"if",0}, {"then",1}, {"else",2} };

    int N;
    cin >> N;
    string word;
    vector<int> pascal;

    int next_then = 0;
    for(int i=0;i<N;i++){
        cin >> word;
        //check (if then)
        if ((next_then && str2int[word] != 1) || (!next_then && str2int[word] == 1))
        {
            cout << "NO" << endl; 
            return 0;
        }
        if( str2int[word] == 0){
            next_then = 1;
            continue;
        }else{
            next_then = 0;
        }

        //next then
        if(str2int[word]%3 == 1){
            //push in stack;
            pascal.push_back(str2int[word]);
        }else{
            //pop
            //(then end) special case
            while(!pascal.empty() && str2int[word]==8 && pascal.back()==1){
                pascal.pop_back();
            } 
            //normal case
            if(pascal.empty() || str2int[word]- pascal.back() != 1){
                //stack empty or nat match
                cout<<"NO"<<endl;
                return 0;
            }else{
                pascal.pop_back();
            }
        }
    }
    while (!pascal.empty() && pascal.back() == 1)
    {
        //only then left
        pascal.pop_back();
    }
    if(!pascal.empty() || next_then == 1){
        cout<< "NO" <<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    return 0;
}



//分成两不检查，逻辑会简单很多
//先检查if then 结构， 再检查配对情况
void solution(){
    map<string, int> str2int = {{"begin", 7}, {"end", 8}, {"if", 0}, {"then", 1}, {"else", 2}};

    int N;
    cin >> N;
    string word;
    vector<int> pascal;
    vector<int> stack;

    for(int i=0;i<N;i++){
        cin >> word;
        pascal.push_back(str2int[word]);
    }
    //check if then
    for(int i=0;i<N;i++){
        if (pascal[i] == 0 && (i == N - 1 || pascal[i + 1] != 1))
        {
            cout << "NO" <<endl;
            return;
        }
        if (pascal[i] == 1 &&( i==0 || pascal[i-1] !=0 ) ){
            cout << "NO" << endl;
            return;
        }
    }
    // check by stack
    for(int i=0;i<N;i++){
        if (pascal[i] == 0)continue;
        if (pascal[i]%3==1){
            //push
            stack.push_back(pascal[i]);
        }else{
            //pop
            while(!stack.empty()&& pascal[i]==8 && stack.back()==1) stack.pop_back();
            //check leagal
            if(stack.empty() || pascal[i] - stack.back() !=1){
                cout<<"NO"<<endl;
                return;
            }else{
                stack.pop_back();
            }
        }
    }
    //pop all legal then
    while(!stack.empty()&&stack.back()==1)stack.pop_back();
    if(!stack.empty()){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;

}