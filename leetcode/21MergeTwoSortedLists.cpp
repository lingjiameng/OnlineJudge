#include <iostream>

using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
};
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)return l2;
        if (l2 == nullptr)return l1;
        ListNode *tail = new ListNode(0), *head = tail;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val <= l2->val)
            {
                tail->next = l1;
                tail = tail->next;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                tail = tail->next;
                l2 = l2->next;
            }
        }
        if (l1 != nullptr)tail->next = l1;
        if (l2 != nullptr)tail->next = l2;
        return head->next;
    }
};

int main(){
    return 0;
}