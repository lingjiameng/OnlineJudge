#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        map<char,string> phone={
            {'2',"abc"},
            {'3',"def"},
            {'4',"ghi"},
            {'5',"jkl"},
            {'6',"mno"},
            {'7',"pqrs"},
            {'8',"tuv"},
            {'9',"wxyz"}
        };
        vector<string> ans;
        string sstack = "";
        string dstack = "";

        dstack.push_back(digits[0]);
        while(!dstack.empty()){
               dstack.pop_back(); 
        }


        for (int i=0;i<digits.size();i++){
            string chars = phone[digits[i]];
            for(int j=0;j< chars.size();j++){
                sstack.push_back(chars[j]);
            }
        }
    }

};

class SolutionRecursive{
private:
    map<char, string> phone = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}};

    vector<string> letterCombinations(string digits,int d){
        vector<string> ans={""};
        if(d<0) return ans;
        ans.clear();
        vector<string> letterPrev = letterCombinations(digits, d - 1);

        for(auto pt=letterPrev.begin(); pt!=letterPrev.end();pt++){
            string chars = phone[digits[d]];
            // cout << digits[d] << chars << endl;
            for (auto cpt =chars.begin(); cpt !=chars.end();cpt++)
                ans.push_back((*pt) + (*cpt));
        }
        return ans;
    }

public:
    vector<string> letterCombinations(string digits){
        if (0 == digits.size())return {};
        return letterCombinations(digits, digits.size() - 1);
    }
};

int main()
{
    SolutionRecursive mySol;
    vector<string> res = mySol.letterCombinations("23");
    // cout<<"!!"<<endl;
    for(auto pt=res.begin();pt!=res.end();pt++){
        cout<< *pt <<endl;
    }
    return 0;
}