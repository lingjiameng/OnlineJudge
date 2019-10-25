#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL){}
};

class mycomp
{
public:
    bool operator()(const ListNode *p1, const ListNode *p2) const{
        return p1->val > p2->val;
    }
};

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {

        for(int ptr =lists.size()-1;ptr >=0 ;ptr--){
            if(lists[ptr] == nullptr)lists.erase(lists.begin()+ptr);
        } //去除掉列表中的空指针
        if(lists.size()==0)return nullptr; //列表为空
        ListNode * head = nullptr,*tail = new ListNode(0); 
        priority_queue<ListNode*,vector<ListNode*>,mycomp> mypq(lists.begin(),lists.end());//自定义的优先队列
        head = mypq.top();
        while(!mypq.empty()){
            tail->next = mypq.top();
            mypq.pop();
            tail= tail->next;
            if(tail->next != nullptr) mypq.push(tail->next);
        }
        return head;
    }
};

int main(){
    Solution mySol;

    ListNode a(1),b(2),c(3);
    a.next = &b;
    b.next = &c;
    ListNode d(2), e(3),f(4);
    e.next = &f;
    d.next = &e;
    vector<ListNode*> list = {&a,&d,nullptr};
    ListNode * res =  mySol.mergeKLists(list);
    
    while(res){
        cout << res->val<<" ";
        res = res->next;
    }
    cout<<endl;
    return 0;
}