#include <iostream>
#include <string>

#define LINTSIZE 100000 //数组的块数,调整高精度数的位数范围
#define BLOCKSIZE 8  //用右式可自动调节大小 (2*sizeof(int))   
                    //每块存储数据的位数 [0, 10^BBLOCKSIZE]
#define BASE 100000000  

//如下设置可以满足加减法需求
//  int            blocksize            base
//int 32bits -> 8位十进制(实际可以9位) ->100000000 
//int 16bits -> 4位十进制 -> 10000

//如下设置才可满足加减乘除需求
//  int            blocksize          base
//int 32bits -> 4位十进制(实际可以9位) ->10000 
//int 16bits -> 2位十进制 -> 100

// #define EMPTYFLAG -1 //空块的flag
using namespace std;

struct _quot_rmndr
{
    string quot;
    string rmndr;
};

class lint
{
    //实现长整数的加法，减法，乘法，
    //TODO 除法
private:
    int digits[LINTSIZE]; 
    //每四位存储为一块，每块的最大存储范围【-32768,32768】，
    //实际使用【0,9999】
    //相对于阅读顺序倒序存储
    int size; // 占用了多少块【0，LINTSIZE-1】
    int sign; // 数的正负,负数为-1，正数为0
    // string data; // lint的完整string形式，用于IO

    void from_string(const string &data); //从data分析出其他三部分数据
    void from_digits(int * arr, int arr_size, int arr_sign); //digits 转化为string
public:
    lint();
    lint(const char* &src);
    lint(const string &src);
    lint(const int &src);
    lint(const lint &src);

    string str() const; //输出string
    int _comp(const lint &num) const; //大于num 返回1，相等返回0， 小于 lint2 返回-1
    int _comp_abs(const lint &num) const;
    lint _add(const lint & num) const; //加法
    lint _minus(const lint &num) const; //减法
    lint _multi(const lint &num) const; //乘法 
    lint _devide(const lint &num) const; //除法
    lint _mod(const lint &num) const; //取余
    _quot_rmndr _dvd(const lint &num) const; //商的范围0-9的除法
    ~lint(){};
};

//将string转换为lint
void lint::from_string(const string &src){
    const string & data = src;
    sign = -1 * (data[0] == '-');
    size = (data.size() + sign - 1) / BLOCKSIZE + 1;
    //转换为digits
    for (int i = 0; i < size; i += 1)
    {
        digits[i] = 0;
        int dpow = 1;
        for (int j = 0; BLOCKSIZE * i + j < (int)data.size() + sign && j < BLOCKSIZE; j++)
        {
            digits[i] += (data[data.size() - BLOCKSIZE * i - j - 1] - '0') * dpow;
            dpow = dpow*10;
        }
    }
    //去掉开头的 0
    for (; size > 0 && digits[size - 1] == 0; size--){}
}

void lint::from_digits(int * arr,int arr_size,int arr_sign){
    size = arr_size;
    sign = arr_sign;
    for(int i=0;i<size;i++){
        digits[i] = arr[i];
    }
    //去掉开头的 0
    for (; size > 0 && digits[size - 1] == 0; size--){}
}

string lint::str() const{
    string data = "",tmp = "";
    for (int i = 0; i < size -1; i++)
    {
        tmp = std::to_string(digits[i]);
        tmp = string( BLOCKSIZE - tmp.size(),'0') + tmp;
        data = tmp + data;
    }
    data = std::to_string(digits[size-1]) + data;
    if (sign == -1)
        data = '-' + data;
    return data;
}

lint::lint(){
    string tmp = "0";
    from_string(tmp);
}

lint::lint(const char* &src){
    //默认为只带有+-号的非空字符串
    string tmp = string(src);
    from_string(tmp);
}

lint::lint(const string &src){
    from_string(src);
}

lint::lint(const int &src){
    string tmp = std::to_string(src);
    from_string(tmp);
}

//拷贝构造函数
lint::lint(const lint &src){
    from_digits( (int *)src.digits,src.size,src.sign);
}

//两数求和
lint lint::_add(const lint &num) const
{
    lint res;
    //两个长整数同号时
    if(sign == num.sign){
        res.sign = sign;
        int carry = 0, sum = 0;
        for(res.size=0;res.size<size && res.size < num.size ; res.size++){
            sum = digits[res.size] + num.digits[res.size] + carry;
            carry = sum / BASE;
            res.digits[res.size] = sum % BASE;
        }
        for (; res.size < size ; res.size++)
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
        if(carry!=0){
            res.digits[res.size] = carry;
            res.size++;
        }
    }else{ //两者异号.TODO:减法
        //步骤比较复杂，
        //比较绝对值大小 -> 大减小 -> 逐块相减并借位 -> 重新计算位数
        
        //比较绝对值大小
        int comp = _comp_abs(num);
        if(comp==0) return lint();
        //比较大小完毕
        const lint *small,*big;
        if( comp == -1  ){//小于
            small = this;
            big = &num; 
        }else{
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
            carry = (diff>=0)-1;
            diff -= carry*BASE;
            res.digits[res.size] = diff;
        }
        
        //去掉开头的 0
        for(;res.size > 0 && res.digits[res.size-1]==0; res.size--){}

        //返回结果
    }
    return res;
}

//两个数做差
lint lint::_minus(const lint &num) const{
    lint tmp(num);
    tmp.sign = (tmp.sign+1)*-1;
    return _add(tmp);
}

//两个数的乘法
lint lint::_multi(const lint &num) const{
    lint res,tmp; //默认值为0

    //特殊情况,如果其中一个值为0
    if(_comp_abs(res)==0 || num._comp_abs(res)==0)return res;
    //同号得正，异号得负。
    tmp.sign = (sign==num.sign)-1;
    
    //模仿算式乘法对第二个数每段分别计算一个乘积，然后将乘积累加。
    long long int carry = 0, product = 0;
    int i1 = 0, i2 = 0;
    for (i2 = 0 ; i2 < num.size; i2++)
    {   
        //第i2段程式结果低位置零
        for (int i = 0; i < i2; i++) tmp.digits[i]=0; //乘积相应位数置零
        
        carry = 0;
        //对每段乘积累计求和并进位,乘积等于之前求和的值加上乘积加上进位
        for(i1=0;i1<size;i1++){
            product = (long long int)digits[i1] * (long long int)num.digits[i2] + carry;
            carry = product / BASE;
            tmp.digits[i1 + i2] = product % BASE;
        }
        tmp.size = i1+i2;
        if (carry != 0)
        {
            tmp.digits[tmp.size] = carry;
            tmp.size++;
        }
        res = res._add(tmp);
    }

    return res;
}

//两个正数的除法
lint lint::_devide(const lint &num) const{
//lint1 / lint2  得 n 余 s
// 模拟除法,逐步增大对lint1的切片，状态会从 1 到 2 ，再回到 1
// 1 abs lint1[part] <= lint2 商 0 余 kint1
// 2 abs lint1[part] > lint2 位数相同或者多一位 倍数在1-9之间，通过减法求商和余数，余数再放入下一轮进行计算
    string this_str = this->str();
    string rmndr = "", quot = "";

    lint tmp; //remainder,quotient;
    for( auto c : this_str){ //从高位到低位依次计算商和余数
        tmp.from_string(rmndr + c); //余数乘10加入本次运算
        _quot_rmndr mods = tmp._dvd(num); //对当前数取余
        quot = quot + mods.quot; //累计的商乘10加上当前商
        rmndr = mods.rmndr;
    }
    return lint(quot);
}

//对两个数取余
lint lint::_mod(const lint &num) const{
    string this_str = this->str();
    string rmndr = "", quot = "";

    lint tmp; //remainder,quotient;
    for (auto c : this_str)
    {                                     //从高位到低位依次计算商和余数
        tmp.from_string(rmndr + c);       //余数乘10加入本次运算
        _quot_rmndr mods = tmp._dvd(num); //对当前数取余
        quot = quot + mods.quot;          //累计的商乘10加上当前商
        rmndr = mods.rmndr;
    }
    return lint(rmndr);
}

//商的范围0-9的特定除法，_devide的辅助函数
_quot_rmndr lint::_dvd(const lint &num) const{
    
    _quot_rmndr res;
    int comp = _comp_abs(num);

    if (comp ==-1){ // 小于num
        res.quot = "0";
        res.rmndr = this->str();
    }else if( comp ==0){ //等于num
        res.quot = "1";
        res.rmndr = "0";
    }else if(comp == 1){ //大于num
        int quot = 0;
        lint rmndr(*this);
        while(rmndr._comp_abs(num)>=0){
            rmndr = rmndr._minus(num);
            quot++;
        }
        res.quot =  '0' + quot;
        res.rmndr = rmndr.str();
    }
    return res;
} 


//两个数大小比较|| -1 小于 || 0 等于 || 1 大于  ||
int lint::_comp(const lint &num) const{
    //比较符号
    if(sign < num.sign)return -1;
    if(sign > num.sign)return 1;
    
    //比较大小 
    int res = 2*sign+1; 
    if(size < num.size) return -res;
    if(size > num.size) return  res;
    
    //比较具体数据
    for(int i = size-1; i>= 0 ; i--){
        if(digits[i] < num.digits[i]) return -res;
        if(digits[i] > num.digits[i]) return  res;
    }
    //最终两个数相等
    return 0;
}

//两个数绝对值的比较|| -1 小于 || 0 等于 || 1 大于 ||
int lint::_comp_abs(const lint &num) const{
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



int main(){
    string num1,num2;
    // ios::sync_with_stdio(false);
    cin >> num1 >> num2 ;

    lint lnum1(num1),lnum2(num2);

    cout << "=======================结果========================="<< endl;

    cout << "数一: " << lnum1.str() << endl;

    cout << "数二: " << lnum2.str() << endl;

    cout << "  和: " << lnum1._add(lnum2).str() << endl;

    cout << "乘积: " << lnum1._multi(lnum2).str() << endl;

    cout << "  商: " << lnum1._devide(lnum2).str() << endl;

    cout << "余数: " << lnum1._mod(lnum2).str() << endl;

    return 0;
}