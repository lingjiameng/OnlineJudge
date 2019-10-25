#include<vector>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

struct book{
    int id;
    book *next;
    book(int i):id(i),next(nullptr){};
};

int main(){
    int n,id;
    stringstream ss;
    string books;
    scanf_s("%d\n",&n);

    vector<book*> shelf_heads(n,nullptr);
    vector<book*> shelf_tails(n,nullptr);
    for(int i=0;i<n;i++){
        getline(cin,books);
        ss.str(books);
        while(ss>>id){
            if(shelf_heads[i]==nullptr){
                shelf_tails[i] = shelf_heads[i] = new book(id);
            }else{
                shelf_tails[i]->next = new book(id);
                shelf_tails[i] = shelf_tails[i]->next;
            }
        }
        ss.clear();
    }

    //get order
    int x,y;
    for(int i=0;i<n-1;i++){
        cin >>x>>y;
        y--;x--;
        shelf_tails[y]->next = shelf_heads[x];
        shelf_tails[y] = shelf_tails[x]; 
    }
    book *tmp = shelf_heads[y];
    while(tmp!=nullptr){
        cout<<tmp->id<<" ";
        tmp = tmp->next;
    }
    cout <<endl;
    return 0;
}