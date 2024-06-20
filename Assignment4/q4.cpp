#include <iostream>
using namespace std;
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next ) return head;
        int len=0;
        ListNode* temp=head;
        while(temp){
            temp=temp->next;
            len++;
        }
        k=k%len;
        if(k==0) return head;
        temp=head;
        for(int i=1;i<=len-k-1;i++){
            temp=temp->next;
        }
        ListNode* temp2=temp->next;
        ListNode* ans=temp2;
        while(temp2->next){
            temp2=temp2->next;
        }
        temp->next=NULL;
        temp2->next=head;
        return ans;
    }
int main(){
    
}