#include <iostream>
#include <string>

#define LINTSIZE 100000 //数组的块数,调整高精度数的位数范围
#define BLOCKSIZE 4  //用右式可自动调节大小 (2*sizeof(int))   
                    //每块存储数据的位数 [0, 10^BBLOCKSIZE]
#define BASE 10000  

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

class lint
{
    //TODO: 实现长整数的加法，减法，乘法，除法
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
    lint _multi(const lint &num) const; //乘法 TODO:
    lint _devide(const lint &num) const; //除法 TODO:
    ~lint(){};
};

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
}

void lint::from_digits(int * arr,int arr_size,int arr_sign){
    size = arr_size;
    sign = arr_sign;
    for(int i=0;i<size;i++){
        digits[i] = arr[i];
    }
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


lint lint::_add(const lint &num) const
{
    lint res;
    int res_digits[LINTSIZE];
    int res_sign,res_size;

    //两个长整数同号时
    if(sign == num.sign){
        res_sign = sign;

        int carry = 0, sum =0;
        for(res_size=0;res_size<size && res_size < num.size ; res_size++){
            sum = digits[res_size] + num.digits[res_size] + carry;
            carry = sum / BASE;
            res_digits[res_size] = sum % BASE;
        }
        for (; res_size < size ; res_size++)
        {
            sum = digits[res_size] + carry;
            carry = sum / BASE;
            res_digits[res_size] = sum % BASE;
        }
        for (; res_size < num.size; res_size++)
        {
            sum = num.digits[res_size] + carry;
            carry = sum / BASE;
            res_digits[res_size] = sum % BASE;
        }
        if(carry!=0){
            res_digits[res_size] = carry;
            res_size++;
        }
        res.from_digits(res_digits,res_size,res_sign);
        // return res;
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
        res_sign = big->sign; //符号和绝对值大的相同
        int carry = 0, diff = 0;

        //计算减法
        for (res_size = 0; res_size < big->size && res_size < small->size; res_size++)
        {
            diff = big->digits[res_size] - small->digits[res_size] + carry;
            carry = (diff >= 0) - 1;
            diff -= carry * BASE;
            res_digits[res_size] = diff;
        }
        for (; res_size < big->size; res_size++)
        {
            diff = big->digits[res_size] + carry;
            carry = (diff>=0)-1;
            diff -= carry*BASE;
            res_digits[res_size] = diff;
        }
        
        //压缩符号大小
        for(;res_size > 0 && res_digits[res_size-1]==0; res_size--){}

        //返回结果
        res.from_digits(res_digits, res_size, res_sign);
        // return res;
    }
    return res;
}

//两个数的乘法
lint lint::_multi(const lint &num) const{
    lint res;
    int res_digits[LINTSIZE];
    int res_sign, res_size;

    //特殊情况,如果其中一个值为0
    if(_comp_abs(res)==0 || num._comp_abs(res)==0)return res;
    //同号得正，异号得负。
    res_sign = (sign==num.sign)-1;
    
    //对第二个数每段分别计算一个乘积，然后将乘积累加。

    int carry = 0, quot = 0;
    int i1 = 0, i2 = 0;
    for (i2 = 0 ; i2 < num.size; i2++)
    { //第i2段
        for (int i = 0; i < i2; i++) res_digits[i]=0; //乘积相应位数置零

        carry = 0;
        //对每段乘积累计求和并进位,乘积等于之前求和的值加上乘积加上进位
        for(i1=0;i1<size;i1++){
            quot = digits[i1] * num.digits[i2] + carry;
            carry = quot / BASE;
            res_digits[i1 + i2] = quot % BASE;
        }
        res_size = i1+i2;
        if (carry != 0)
        {
            res_digits[res_size] = carry;
            res_size++;
        }
        lint tmp;
        tmp.from_digits(res_digits,res_size,res_sign);
        res = res._add(tmp);
    }
    return res;
}

//两个数的除法
lint lint::_devide(const lint &num) const{
    lint res;
    
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
    // cout << lnum2.str() <<endl;

    // lint lnum3(lnum1);
    // cout << lnum3.str()<<endl;

    // cout << lint("12345678916666").str() <<endl;

    // cout << lint(123000).str() << endl;

    cout << lnum1._add(lnum2).str()<<endl;

    //cout << lnum1._multi(lnum2).str() << endl;

    // string sum = lint_add(num1,num2);
    // string quot = lint_quot(num1,num2);

    // cout << "sum: " << sum <<endl;
    // cout << "quotient: " << quot << endl;    
    return 0;
}