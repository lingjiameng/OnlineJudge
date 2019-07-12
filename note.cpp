#include <vector>
#include <iostream>

using namespace std;



int main(int argc, char const *argv[])
{
/*
int i;
引用 int & p = i; 引用即别名，可读写
取地址符 int *p = &i; 
解引用 int & c = *p; 解引用后可读写，所以得到的是引用
 */
    int i = 10;
    int &ri = i;
    int *pi = &i;
    int &rp = *pi;

/*
指针的单位是bytes

对指针 +1 ，指针增加的值是不同的。
因为指针有多种类型 char*，int*等等
每种加法都是单独重载的

而空类型的指针 void * 就没有加法操作

 */

    double p[] = {1.0, 2.0, 3.0};
    cout << p << " : " << *p << " || " << p + 1 << " : " << *(p + 1) << endl;

    int nums[] = {1, 2, 3, 4, 5};
    cout << nums << " : " << *nums << " || " << nums + 1 << " : " << *(nums + 1) << endl;

    return 0;



}
