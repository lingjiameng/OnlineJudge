#include <iostream>  
#include <string>  
using namespace std;  
  
const int dayofmonth[2][13] = { { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },  
{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } };  
void getdate(int &y, int &m, int &d)  
{  
    string date;  
        cin >> date;  
    y = (date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0');  
    m = (date[5] - '0') * 10 + (date[6] - '0');  
    d = (date[8] - '0') * 10 + (date[9] - '0');  
}  
int getweek(int y, int m, int d)  
{  
    int yy = y, mm = m;  
    if (mm == 1 || mm == 2)  
    {  
        yy--;  
        mm += 12;  
    }  
    int w = (d + mm * 2 + (mm + 1) * 3 / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;  
    return w + 1;  
}  
bool isleap(int y)  
{  
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);  
}  
bool isequal(int y1, int m1, int d1, int y2, int m2, int d2)  
{  
    return y1 == y2&&m1 == m2&&d1 == d2;  
}  
bool isdeal(int y, int m, int d)  
{  
    if (getweek(y, m, d) == 6 || getweek(y, m, d) == 7)  
        return false;  
    if ((m == 1 && d == 1) || (m == 5 && d >= 1 && d <= 3) || (m == 10 && d >= 1 && d <= 7))  
        return false;  
    return true;  
}  
void getnextdate(int &y, int &m, int &d)  
{  
    if (d < dayofmonth[isleap(y)][m])  
        d++;  
    else if (m < 12)  
    {  
        m++;  
        d = 1;  
    }  
    else  
    {  
        y++;  
        m = 1;  
        d = 1;  
    }  
}  
int dealdayperyear(int y)  
{  
    int v1 = 0;  
    if (isleap(y))  
        v1 = isdeal(y, 12, 30) + isdeal(y, 12, 31);  
    else  
        v1 = isdeal(y, 12, 31);  
    int v2 = 52 * 7;  
    int v3 = 11;  
    int v4 = 52 * 2;  
    int v5 = 0;  
    if (getweek(y, 1, 1) == 6 || getweek(y, 1, 1) == 7)  
        v5++;  
    for (int i = 1; i < 4; i++)  
        if (getweek(y, 5, i) == 6 || getweek(y, 5, i) == 7)  
            v5++;  
    for (int i = 1; i < 8; i++)  
        if (getweek(y, 10, i) == 6 || getweek(y, 10, i) == 7)  
            v5++;  
    return v1 + v2 - v3 - v4 + v5;  
}  
void solve()  
{  
    int y1, m1, d1, y2, m2, d2;  
    getdate(y1, m1, d1);  
    getdate(y2, m2, d2);  
    int dealday = 0;  
    getnextdate(y2, m2, d2);  
    if (y1 == y2)  
    {  
        while (!isequal(y1, m1, d1, y2, m2, d2))  
        {  
            if (isdeal(y1, m1, d1))  
                dealday++;  
            getnextdate(y1, m1, d1);  
        }  
    }  
    else  
    {  
        int flag = y1;  
        while (!isequal(y1, m1, d1, flag + 1, 1, 1))  
        {  
            if (isdeal(y1, m1, d1))  
                dealday++;  
            getnextdate(y1, m1, d1);  
        }  
        for (int i = y1; i < y2; i++)  
            dealday += dealdayperyear(i);  
        y1 = y2; m1 = 1; d1 = 1;  
        while (!isequal(y1, m1, d1, y2, m2, d2))  
        {  
            if (isdeal(y1, m1, d1))  
                dealday++;  
            getnextdate(y1, m1, d1);  
        }  
    }  
    cout << dealday << endl;  
}  
int main()  
{  
    int n;  
    cin >> n;  
    while (n--)  
    {  
        solve();  
    }  
    return 0;  
}  