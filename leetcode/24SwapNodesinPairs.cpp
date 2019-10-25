#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        ListNode *first, *second, *newhead = new ListNode(0);
        newhead->next = head;
        head = newhead;
        while (head && head->next && head->next->next){
            first = head->next;
            second = head->next->next;
            first->next = second->next;
            second->next = first;

            head->next = second;
            head = first;
        }
        return newhead->next;
    }
};

int main(){
    Solution mySol;

    ListNode a(1), b(2), c(3),d(4);
    a.next = &b;
    b.next = &c;
    c.next = &d;

    ListNode *res = mySol.swapPairs(&a);
    while (res)
    {
        cout << res->val << " ";
        res = res->next;
    }
    cout << endl;
    return 0;
}