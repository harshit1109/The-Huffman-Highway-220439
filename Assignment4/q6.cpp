#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
class Node{
    int val;
    Node* left;
    Node* right;
    Node(int val){
        this->val=val;
        left=NULL;
        right=NULL;
    }
    bool isIsomorphic(Node *a,Node *b){
        if(a==NULL&&b==NULL) return true;
        if(a!=NULL&&b!=NULL) return isIsomorphic(a->left,b->left)&&isIsomorphic(a->right,b->right);
        return false;
    }
};
int main(){
    
}