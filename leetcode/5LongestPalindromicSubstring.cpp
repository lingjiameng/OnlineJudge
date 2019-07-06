#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

bool checkPalindromic(string s)
{

    for (int i = 0, j = s.size() - 1; i < j; ++i, --j)
    {
        if (s[i] != s[j])
            return false;
    }
    return true;
}

string longestPalindrome(string s)
{
    //O(n3)time limit exceeded
    //low effciency in only short solution
    int maxLength = 1;
    string rtn = string("") + s[0];
    for (int i = 0; i < s.size(); ++i)
    {
        for (int j = i + 1; j < s.size(); ++j)
        {
            if (j - i + 1 > maxLength && checkPalindromic(s.substr(i, j - i + 1)))
            {
                maxLength = j - i + 1;
                rtn = s.substr(i, j - i + 1);
            }
        }
    }
    return rtn;
}

string longestPalindrome_beta(string s)
{
    //O(n2)check by symmetry axis
    int length = s.size(), maxLength = 0, d = 0, rtni = 0;
    // alphabeta is axis
    for (int i = 0; i < length; ++i)
    {
        for (d = 0; i - d >= 0 && i + d < length && s[i - d] == s[i + d]; ++d)
            ;
        if (--d * 2 + 1 > maxLength)
        {
            maxLength = d * 2 + 1;
            rtni = i - d;
        }
        for (d = 0; i - d - 1 >= 0 && i + d < length && s[i - d - 1] == s[i + d]; ++d)
            ;
        // cout << i << d<< endl;
        if (d-- * 2 > maxLength)
        {
            maxLength = d * 2 + 2;
            rtni = i - d - 1;
        }
    }
    return s.substr(rtni, maxLength);
}


string longestPalindromeManacher(string s){
    string tmp="$";
    //expand string
    for(int i=0;i<s.size();i++){
        tmp += '#';
        tmp += s[i];
    }
    tmp += "#@";
    // cout << "expand:"<<tmp<<endl;

    vector<int> len(tmp.size(),0);
    //manacher search
    int maxp=0,maxi=1,maxl=0,rtni=0;
    for(int i=1; i<tmp.size()-1;i++){
        if (i < maxi && len[2 * maxp - i] < maxi - i)
        {
            len[i] = len[2 * maxp - i];
        }  
        else{
            int d = 0;
            for (d = 0; tmp[maxi + d] == tmp[2 * i - maxi - d]; ++d)
                ;
            maxp = i;
            maxi = maxi + --d;
            len[i] = maxi - i + 1;
            if(maxl<len[i]-1){
                rtni=i;
                maxl = len[i]-1;
            }
        }
    }
    // cout<<"len   :";
    // for(int i=0;i<tmp.size();++i){
    //     cout<<len[i];
    // }
    // cout<<endl;
    // cout<< maxl<<endl;
    // cout<< s.substr((rtni-maxl-1)/2,maxl)<<endl;
    //todo debug
    return s.substr((rtni - maxl - 1) / 2, maxl);
}

int main()
{
    cout<< longestPalindromeManacher("sdfadgasdfsaeadsgafeaasgadsfjkvhirugahfahdsjkfhagr")<<endl;
    return 0;
}