#include <iostream>
#include <string>
//高精度幂

#define ul unsigned long
#define LINTSIZE 100000 //数组的块数,调整高精度数的位数范围
#define BLOCKSIZE 8     //用右式可自动调节大小 (2*sizeof(int)) 每块存储数据的位数 [0, 10^BBLOCKSIZE]
#define BASE 100000000

//如下设置可以满足需求
//  int            blocksize            base
//int 32bits -> 8位十进制(实际可以9位) ->100000000
//int 16bits -> 4位十进制 -> 10000

using namespace std;

class ZeroDivisionError
{
};

ul len(const char *p)
{
    ul l = 0;
    while (p[l] != '\0')
        l++;
    return l;
}

//高精度整数类，实现了加减乘除和取模
class lint
{
private:
    int digits[LINTSIZE];
    //每四位存储为一块，每块的最大存储范围【-32768,32768】，
    //实际使用【0,9999】
    //相对于阅读顺序倒序存储
    ul size;  // 占用了多少块【0，LINTSIZE-1】
    int sign; // 数的正负,负数为-1，正数为0
    // string data; // lint的完整string形式，用于IO

    void from_digits(int *arr, ul arr_size, int arr_sign); //digits 转化为string
    void from_chars(const char *data);
    lint _dvd(const lint &num, int &quot) const;

public:
    lint();                //默认值
    lint(const char *src); //字符数组
    lint(int src);         //整数
    lint(const lint &src); //拷贝构造函数

    char *str(char *out) const;           //输出字符串
    int _comp(const lint &num) const;     //大于num 返回1，相等返回0， 小于 lint2 返回-1
    int _comp_abs(const lint &num) const; //比较绝对值，结果同上
    lint _add(const lint &num) const;     //加法
    lint _minus(const lint &num) const;   //减法
    lint _multi(const lint &num) const;   //乘法
    lint _devide(const lint &num) const;  //除法
    lint _mod(const lint &num) const;     //取余
    ~lint(){};
};

void lint::from_chars(const char *data)
{
    sign = -1 * (data[0] == '-');

    ul data_len = len(data);
    size = (data_len + sign - 1) / BLOCKSIZE + 1;
    //从字符串的尾部 到 头部 转换为digits的 头部 到 尾部
    for (ul i = 0; i < size; i += 1)
    {
        digits[i] = 0;
        int dpow = 1;
        for (int j = 0; BLOCKSIZE * i + j < data_len + sign && j < BLOCKSIZE; j++)
        {
            digits[i] += (data[data_len - BLOCKSIZE * i - j - 1] - '0') * dpow;
            dpow = dpow * 10;
        }
    }
    //去掉开头的 0
    while (size > 1 && digits[size - 1] == 0)
        size--;
}

//从数组获取值
void lint::from_digits(int *arr, ul arr_size, int arr_sign)
{
    size = arr_size;
    sign = arr_sign;
    for (ul i = 0; i < size; i++)
    {
        digits[i] = arr[i];
    }
    //去掉开头的 0
    while (size > 1 && digits[size - 1] == 0)
        size--;
}

//转化为可打印的字符数组
char *lint::str(char *p) const
{
    int bases[BLOCKSIZE], tmp = BASE;
    for (int i = 0; i < BLOCKSIZE; i++)
    {
        tmp /= 10;
        bases[i] = tmp;
    }

    if (sign == -1)
        p[0] = '-';

    ul delta = -sign;

    //最高位的数字块，不补零
    tmp = digits[size - 1];
    for (int j = 0; j < BLOCKSIZE; j++)
    {
        p[delta] = '0' + tmp / bases[j];
        tmp = tmp % bases[j];
        if (p[delta] != '0' || delta + sign != 0)
            delta++; //去掉前面的0
    }

    //处理剩余的数字块，需要补零
    ul i = 0, j = 0;
    for (i = 0; i < size - 1; i++)
    {
        tmp = digits[size - i - 2];
        for (j = 0; j < BLOCKSIZE; j++)
        {
            p[delta + i * BLOCKSIZE + j] = '0' + tmp / bases[j];
            tmp = tmp % bases[j];
        }
    }
    p[delta + i * BLOCKSIZE] = '\0';
    return p;
}

//默认空构造函数
lint::lint()
{
    char tmp[] = "0";
    from_chars(tmp);
}

//字符数组构造函数
lint::lint(const char *src)
{
    from_chars(src);
}

//整数构造函数
lint::lint(int src)
{
    sign = (src >= 0) - 1;
    int quot = src;
    size = 0;
    do
    {
        digits[size++] = quot % BASE;
        quot = quot / BASE;
    } while (quot != 0);
}

//拷贝构造函数
lint::lint(const lint &src)
{
    from_digits((int *)src.digits, src.size, src.sign);
}

//两数求和
lint lint::_add(const lint &num) const
{
    lint res;
    //两个长整数同号时
    if (sign == num.sign)
    {
        res.sign = sign;
        int carry = 0, sum = 0;
        for (res.size = 0; res.size < size && res.size < num.size; res.size++)
        {
            sum = digits[res.size] + num.digits[res.size] + carry;
            carry = sum / BASE;
            res.digits[res.size] = sum % BASE;
        }
        for (; res.size < size; res.size++)
        {
            sum = digits[res.size] + carry;
            carry = sum / BASE;
            res.digits[res.size] = sum % BASE;
        }
        for (; res.size < num.size; res.size++)
        {
            sum = num.digits[res.size] + carry;
            carry = sum / BASE;
            res.digits[res.size] = sum % BASE;
        }
        if (carry != 0)
        {
            res.digits[res.size] = carry;
            res.size++;
        }
    }
    else
    { //两者异号.TODO:减法
        //步骤比较复杂，
        //比较绝对值大小 -> 大减小 -> 逐块相减并借位 -> 重新计算位数

        //比较绝对值大小
        int comp = _comp_abs(num);
        if (comp == 0)
            return lint();
        //比较大小完毕
        const lint *small, *big;
        if (comp == -1)
        { //小于
            small = this;
            big = &num;
        }
        else
        {
            small = &num;
            big = this;
        }

        //绝对值大减小
        res.sign = big->sign; //符号和绝对值大的相同
        int carry = 0, diff = 0;

        //计算减法
        for (res.size = 0; res.size < big->size && res.size < small->size; res.size++)
        {
            diff = big->digits[res.size] - small->digits[res.size] + carry;
            carry = (diff >= 0) - 1;
            diff -= carry * BASE;
            res.digits[res.size] = diff;
        }
        for (; res.size < big->size; res.size++)
        {
            diff = big->digits[res.size] + carry;
            carry = (diff >= 0) - 1;
            diff -= carry * BASE;
            res.digits[res.size] = diff;
        }

        //去掉开头的 0
        while (res.size > 1 && res.digits[res.size - 1] == 0)
            res.size--;
        //返回结果
    }
    return res;
}

//两个数做差
lint lint::_minus(const lint &num) const
{
    lint tmp(num);
    tmp.sign = (tmp.sign + 1) * -1;
    return _add(tmp);
}

//两个数的乘法
lint lint::_multi(const lint &num) const
{
    lint res, tmp; //默认值为0

    //特殊情况,如果其中一个值为0
    if (_comp_abs(res) == 0 || num._comp_abs(res) == 0)
        return res;
    //同号得正，异号得负。
    tmp.sign = (sign == num.sign) - 1;

    //模仿算式乘法对第二个数每段分别计算一个乘积，然后将乘积累加。
    long long int carry = 0, product = 0;
    ul i1 = 0, i2 = 0;
    for (i2 = 0; i2 < num.size; i2++)
    {
        //第i2段程式结果低位置零
        for (ul i = 0; i < i2; i++)
            tmp.digits[i] = 0; //乘积相应位数置零

        carry = 0;
        //对每段乘积累计求和并进位,乘积等于之前求和的值加上乘积加上进位
        for (i1 = 0; i1 < size; i1++)
        {
            product = (long long int)digits[i1] * (long long int)num.digits[i2] + carry;
            carry = product / BASE;
            tmp.digits[i1 + i2] = product % BASE;
        }
        tmp.size = i1 + i2;
        if (carry != 0)
        {
            tmp.digits[tmp.size] = carry;
            tmp.size++;
        }
        res = res._add(tmp);
    }

    return res;
}

//两个数的除法
lint lint::_devide(const lint &num) const
{
    /* lint1 / lint2  得 n 余 s
    // 模拟除法,逐步增大对lint1的切片，状态会从 1 到 2 ，再回到 1
    // 1 abs lint1[part] <= lint2 商 0 余 kint1
    // 2 abs lint1[part] > lint2 位数相同或者多一位 倍数在1-9之间，通过减法求商和余数，余数再放入下一轮进行计算
    // 同号整除，商 和 余数 同号
    // 异号整除，商负 余同除数
    */
    //异常检查
    if (num._comp_abs(0) == 0)
        throw ZeroDivisionError();

    lint num1(*this), num2(num); //绝对值复制
    num1.sign = num2.sign = 0;

    lint rmndr, quot, tmp;
    int res_sign;
    if (sign == num.sign)
    { //同号除法
        res_sign = num.sign;
    }
    else
    {                  //异号除法
        res_sign = -1; //商的符号为负
        num1 = num1._add(num2);
    }

    char num1_str[LINTSIZE * BLOCKSIZE + 10];
    num1.str(num1_str);

    int tmp_quot = 0;
    for (ul i = 0; i < len(num1_str); i++)
    {                                                   //从高位到低位依次计算商和余数
        tmp = rmndr._multi(10)._add(num1_str[i] - '0'); //余数乘10加入本次运算
        rmndr = tmp._dvd(num2, tmp_quot);               //对当前数取余
        quot = quot._multi(10)._add(tmp_quot);          //累计的商乘10加上当前商
    }

    if (quot.size != 1 || quot.digits[0] != 0)
        quot.sign = res_sign;
    return quot;
}

//两个数取余
lint lint::_mod(const lint &num) const
{
    if (num._comp_abs(0) == 0)
        throw ZeroDivisionError();

    lint num1(*this), num2(num); //绝对值复制
    num1.sign = num2.sign = 0;

    lint rmndr, quot, tmp;
    int res_sign = num.sign; //同号时符号相同，异号时余数符号和除数符号相同
    if (sign != num.sign)    //异号补数
        num1 = num1._add(num2);
    char num1_str[LINTSIZE * BLOCKSIZE + 10];
    num1.str(num1_str);

    int tmp_quot = 0;
    for (ul i = 0; i < len(num1_str); i++)
    {                                                   //从高位到低位依次计算商和余数
        tmp = rmndr._multi(10)._add(num1_str[i] - '0'); //余数乘10加入本次运算
        rmndr = tmp._dvd(num2, tmp_quot);               //对当前数取余
        quot = quot._multi(10)._add(tmp_quot);          //累计的商乘10加上当前商
    }

    if (sign != num.sign) //异号补数
        rmndr = num2._minus(rmndr);
    if (rmndr.size != 1 || rmndr.digits[0] != 0)
        rmndr.sign = res_sign;
    return rmndr;
}

//商的范围0-9的特定除法，_devide的辅助函数
lint lint::_dvd(const lint &num, int &quot) const
{

    int comp = _comp_abs(num);

    if (comp == -1)
    { // 小于num
        quot = 0;
        return *this;
    }
    else if (comp == 0)
    { //等于num
        quot = 1;
        return lint(0);
    }
    //大于num
    quot = 0;
    lint rmndr(*this);
    while (rmndr._comp_abs(num) >= 0)
    {
        rmndr = rmndr._minus(num);
        quot++;
    }
    return rmndr;
}

//两个数大小比较|| -1 小于 || 0 等于 || 1 大于  ||
int lint::_comp(const lint &num) const
{
    //比较符号
    if (sign < num.sign)
        return -1;
    if (sign > num.sign)
        return 1;

    //比较大小
    int res = 2 * sign + 1;
    if (size < num.size)
        return -res;
    if (size > num.size)
        return res;

    //比较具体数据
    for (int i = size - 1; i >= 0; i--)
    {
        if (digits[i] < num.digits[i])
            return -res;
        if (digits[i] > num.digits[i])
            return res;
    }
    //最终两个数相等
    return 0;
}

//两个数绝对值的比较|| -1 小于 || 0 等于 || 1 大于 ||
int lint::_comp_abs(const lint &num) const
{
    //比较大小
    if (size < num.size)
        return -1;
    if (size > num.size)
        return 1;

    //比较具体数据
    for (int i = size - 1; i >= 0; i--)
    {
        if (digits[i] < num.digits[i])
            return -1;
        if (digits[i] > num.digits[i])
            return 1;
    }
    //最终两个数相等
    return 0;
}

// 重载算术运算符 加减乘除取余和输出流
lint operator+(const lint &num1, const lint &num2) { return num1._add(num2); }
lint operator-(const lint &num1, const lint &num2) { return num1._minus(num2); }
lint operator*(const lint &num1, const lint &num2) { return num1._multi(num2); }
lint operator/(const lint &num1, const lint &num2) { return num1._devide(num2); }
lint operator%(const lint &num1, const lint &num2) { return num1._mod(num2); }
// 重载逻辑运算符
bool operator<(const lint &num1, const lint &num2) { return (num1._comp(num2) == -1); }
bool operator<=(const lint &num1, const lint &num2) { return (num1._comp(num2) != 1); }
bool operator>(const lint &num1, const lint &num2) { return (num1._comp(num2) == 1); }
bool operator>=(const lint &num1, const lint &num2) { return (num1._comp(num2) != -1); }
bool operator==(const lint &num1, const lint &num2) { return (num1._comp(num2) == 0); }
bool operator!=(const lint &num1, const lint &num2) { return (num1._comp(num2) != 0); }

ostream &operator<<(ostream &out, const lint &num)
{
    char p[LINTSIZE * BLOCKSIZE + 10];
    num.str(p);
    return (out << p);
}

int main()
{
    string num;
    int exp;
    while(cin >>num >> exp ){
        //确定小数点的位数，并且从字符串中去除小数点。
        lint points;
        for (unsigned int i = 0; i < num.size(); i++)
        {
            if (num[num.size() - i - 1] == '.')
            {
                points = i;                       //记录小数点的位数
                num.erase(num.size() - i - 1, 1); //去除小数点
                break;
            }
        }

        //构造无小数点的数
        lint lnum(num.c_str()), lexp(exp);

        // if(lnum == 0){
        //     cout<<'0'<<endl;
        //     continue;
        // }
        //计算次方
        lint lres = 1;
        for (unsigned int i = 0; i < lexp; i++)
        {
            lres = lres * lnum;
        }
        points = points * lexp;

        //添加小数点
        char res_str[BLOCKSIZE * LINTSIZE + 10];
        lres.str(res_str);
        string sres(res_str);
        string ans = "";

        // cout <<sres <<"||" <<sres.size()<<endl;
        unsigned int i = 0;
        for (i = 0; i < sres.size() && i < points; i++)
        {
            ans = sres[sres.size() - i - 1] + ans;
        }
        for (; i < points; i++)
        {
            ans = '0' + ans;
        }
        ans = '.' + ans;
        for (; i < sres.size(); i++)
        {
            ans = sres[sres.size() - i - 1] + ans;
        }

        //取出多余的0
        for (i = 0; i < ans.size() && ans[i] == '0'; i++)
        {
        }
        ans.erase(0, i);
        for (i = ans.size() - 1; i >= 0 && (ans[i] == '0' || ans[i] == '.'); i--)
        {
            if (ans[i] == '.')
            {
                i--;
                break;
            }
        }
        i++;
        ans.erase(i, ans.size() - i);
        if(ans.size()!=0)
            cout << ans << endl;
        else
        {
            cout<< "0" <<endl;
        }
            
    }
    return 0;
}