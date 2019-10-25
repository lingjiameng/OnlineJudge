#include <iostream>
using namespace std;
/**
 * Definition for singly-linked list.
 * 
 */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}                               *
};

class Solution
{
    int checkIfKNodes(ListNode *head, int k)
    {
        while (head != nullptr && k > 1)
        {
            k--;
            head = head->next;
        }
        if (head != nullptr)
            return 1;
        return 0;
    }

public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (checkIfKNodes(head, k) == 0)
            return head;

        ListNode *newhead = new ListNode(0);
        ListNode *list = newhead, *tail, *tmp;
        list->next = nullptr;
        while (1 == checkIfKNodes(head, k))
        {
            tail = head; //record tail
            for (int i = 0; i < k; i++)
            {
                tmp = head;
                head = head->next;
                tmp->next = list->next;
                list->next = tmp;
            }
            list = tail; //move ptr to segment start
        }
        list->next = head;
        return newhead->next;
    }
};

int main(){
    return 0;
}