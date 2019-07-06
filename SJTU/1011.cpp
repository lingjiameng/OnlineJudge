#include <iostream>
#include <iomanip>

using namespace std;

class MyComplex
{
    friend istream& operator>>(istream &is,MyComplex& c);
    friend ostream& operator<<(ostream &os,const MyComplex& c);
    friend MyComplex operator+(const MyComplex& c1,const MyComplex& c2);
    friend MyComplex operator-(const MyComplex& c1,const MyComplex& c2);
    friend MyComplex operator*(const MyComplex& c1,const MyComplex& c2);
    friend MyComplex operator/(const MyComplex& c1,const MyComplex& c2);
    friend MyComplex operator+=(MyComplex& c1,const MyComplex& c2);
    friend MyComplex operator-=(MyComplex& c1,const MyComplex& c2);
    friend MyComplex operator*=(MyComplex& c1,const MyComplex& c2);
    friend MyComplex operator/=(MyComplex& c1,const MyComplex& c2);
private:
  double x,y;
public:
  /* Implementation of MyComplex */
  MyComplex(){x=0;y=0;};
  MyComplex(double a,double b){x=a;y=b;};
};

//
istream& operator>>(istream &is,MyComplex& c){
    is>>c.x>>c.y;
    return is;
}
ostream& operator<<(ostream &os,const MyComplex& c){
    os<<setiosflags(ios::fixed)<<setprecision(2)<<c.x<<" "<<c.y;
    return os;
}

//
MyComplex operator+(const MyComplex& c1,const MyComplex& c2){
    MyComplex tmp;
    tmp.x=c1.x+c2.x;
    tmp.y=c1.y+c2.y;
    return tmp;
}
MyComplex operator-(const MyComplex& c1,const MyComplex& c2){
    MyComplex tmp;
    tmp.x=c1.x-c2.x;
    tmp.y=c1.y-c2.y;
    return tmp;
}
MyComplex operator*(const MyComplex& c1,const MyComplex& c2){
    MyComplex tmp;
    tmp.x=c1.x*c2.x-c1.y*c2.y;
    tmp.y=c1.x*c2.y+c1.y*c2.x;
    return tmp;
}
MyComplex operator/(const MyComplex& c1,const MyComplex& c2){
    MyComplex tmp;
    double m=c2.x*c2.x+c2.y*c2.y;
    tmp.x=(c1.x*c2.x+c1.y*c2.y)/m;
    tmp.y=(c1.y*c2.x-c1.x*c2.y)/m;
    return tmp;
}

//
MyComplex operator+=(MyComplex& c1,const MyComplex& c2){
    c1=c1+c2;
    return c1;
}
MyComplex operator-=(MyComplex& c1,const MyComplex& c2){
    c1=c1-c2;
    return c1;
}
MyComplex operator*=(MyComplex& c1,const MyComplex& c2){
    c1=c1*c2;
    return c1;
}
MyComplex operator/=(MyComplex& c1,const MyComplex& c2){
    c1=c1/c2;
    return c1;
}



int main()
{
  MyComplex z1;
  MyComplex z2;

  cin >> z1 >> z2;

  cout << z1 + z2 <<endl;
  cout << z1 - z2 <<endl;
  cout << z1 * z2 <<endl;
  cout << z1 / z2 <<endl;
  cout << (z1 += z2) <<endl;
  cout << (z1 -= z2) <<endl;
  cout << (z1 *= z2) <<endl;
  cout << (z1 /= z2) <<endl;

  return 0;
}