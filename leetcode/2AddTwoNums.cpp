#include <iostream>
#include <vector>
#include <map>

using namespace std;

//solution 逐位相加 没有什么好说的

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    ListNode *rtn = new ListNode((l1->val + l2->val) %10);
    ListNode *tmp = rtn;
    int carry = (l1->val + l2->val)/10;
    l1 = l1->next;
    l2 = l2->next;

    while(l1 != NULL || l2 != NULL)
    {
        tmp->next = new ListNode(carry);
        tmp = tmp->next;
        if(l1 != NULL){
            tmp->val += l1->val;
            l1 = l1->next;
        }
        if(l2 != NULL){
            tmp->val += l2->val;
            l2 = l2->next;
        }
        carry = tmp->val / 10;
        tmp->val = tmp->val % 10;
    }
    if(carry != 0){
        tmp->next = new ListNode(carry);
    }
    return rtn;
}

//我的代码
// ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
// {
//     ListNode *result = new ListNode(0);
//     ListNode *tmp = result;
//     ListNode *tail;
//     int residue = 0;
//     int carry = 0;
//     int sum = 0;

//     while (l1 != NULL && l2 != NULL)
//     {
//         sum = l1->val + l2->val + carry; //对应位求和
//         residue = sum % 10;              //余数记在当前位
//         tmp->val = residue;

//         carry = sum / 10; //进位

//         tmp->next = new ListNode(0);
//         tail = tmp;
//         tmp = tmp->next;
//         l1 = l1->next;
//         l2 = l2->next;
//     }
//     while (l1 != NULL)
//     {
//         sum = l1->val + carry;
//         residue = sum % 10;
//         tmp->val = residue;

//         carry = sum / 10;

//         tmp->next = new ListNode(0);
//         tail = tmp;
//         tmp = tmp->next;
//         l1 = l1->next;
//     }
//     while (l2 != NULL)
//     {
//         sum = l2->val + carry;
//         residue = sum % 10;
//         tmp->val = residue;

//         carry = sum / 10;

//         tmp->next = new ListNode(0);
//         tail = tmp;
//         tmp = tmp->next;
//         l2 = l2->next;
//     }
//     if (carry != 0)
//     {
//         tmp->val = carry;
//     }
//     if (tmp->val == 0)
//     {
//         tail->next = NULL;
//     }

//     return result;
// }

int main(){
    return 0;
}