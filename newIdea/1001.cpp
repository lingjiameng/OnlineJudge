#include <iostream>
#include <stack>
using namespace std;

// 无序数组，输出每一个元素 之后第一个大于该元素的元素


// 采用 栈 来实现，
// 当 当前元素大于栈顶元素时，出栈 并将当前元素作为其结果
// 否则 将当前元素入栈

int main(){
    int n,t;
    cin >> n;
    int *nums = new int[n];
    for(int i=0;i<n;i++){
        cin >>nums[i];
    }
    stack<int> arr; //存储元素的下标
    int *res = new int[n];
    for(int i=0;i<n;i++){
        res[i]= -1;
        //-1 表示没有结果
    }
    arr.push(0);
    int i=1;
    while(i < n){
        while (!arr.empty() && nums[i] > nums[arr.top()])
        {
            res[arr.top()] = nums[i];
            arr.pop();
        }
        arr.push(i);
        i++;
    }

    for(int j=0;j<n-1;j++){
        cout<<res[j]<<" ";
    }
    cout <<endl;
    return 0;
}