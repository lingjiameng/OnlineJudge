#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}                         
};
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *p = head, *target = head;
        while (--n > 0)
            head = head->next; //移动尾节点为第n个节点
        if (head->next == nullptr)
            return p->next; //若果要删除头结点
        else
            head = head->next; //否则将尾节点后移1位，使target指针指向目标节点的父节点
        while (head->next != nullptr)
        { //同时移动头尾指针
            target = target->next;
            head = head->next;
        }
        target->next = target->next->next;
        return p;
    }
};

int main(){
    return 0;
}