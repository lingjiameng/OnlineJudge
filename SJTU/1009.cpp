#include <iostream>
#include <stdio.h>

using namespace std;

//transRecord 交易记录  m次

//priceRecord 价格记录  n个

//买入总花费
double buyCost(int num,int price){
    int shareNum=num*100;

    double totalPrice=shareNum*price*1.0;
    double commission=max(shareNum*price*0.002,5.0);
    double transFee=shareNum/1000.0;
    double communicationFee=1.0;

    return totalPrice+commission+transFee+communicationFee;
}

//售出总花费
double sellCost(int num,int price){
    int shareNum=num*100;

    double commission=max(shareNum*price*0.002,5.0);
    double transFee=shareNum/1000.0;
    double communicationFee=1.0;
    double tax=shareNum*price*0.001;

    return commission+transFee+communicationFee+tax;
}

//售出总收入
double sellIncome(int num,int price){
    return num*price*100.0;
}

//交易净收益
double trans(int num,int price, int opt){
    if(opt==1){
        return buyCost(num,price)*(-1.0);
    }
    //(opt==2)
    return sellIncome(num,price)-sellCost(num,price);

}

int main(){
    int m,n;

    //读入交易记录
    cin>>m;
    int transRecord[m][3];
    for(int i=0;i<m;i++){
        cin>>transRecord[i][0];
        cin>>transRecord[i][1];
        cin>>transRecord[i][2];
        //cout<<"trans: "<<i<<endl;
    }

    //读入价格变化记录
    cin>>n;
    int priceRecord[n][2];
    for(int i=0;i<n;i++){
        cin>>priceRecord[i][0];
        cin>>priceRecord[i][1];
        //cout<<"price: "<<i<<endl;
    }

    //日期记录指针 pDate
    //交易日期指针 pTrans

    int pDate=1,pTrans=0;
    double income=0.0;

    int Tnum=0,Tprice=0,Topt=1;
    for(;pTrans<m;pTrans++){
        Tnum=transRecord[pTrans][1];
        Topt=transRecord[pTrans][2];
        for(;pDate<n;pDate++){
            if(priceRecord[pDate][0]>transRecord[pTrans][0]&& \
            priceRecord[pDate-1][0]<=transRecord[pTrans][0]){
                Tprice=priceRecord[pDate-1][1];
                break;
            }
            else{
                Tprice=priceRecord[pDate][1];
            }
        }
        income+=trans(Tnum,Tprice,Topt);
    }

    printf("%.2f",income);
    
    return 0;
}
