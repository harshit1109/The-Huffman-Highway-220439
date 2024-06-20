#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
string lexo_small(string s){
    string p=s+s;
    priority_queue<string>pq;
    for(int i=0;i<s.length();i++){
       string q="";
       for(int j=i;j<i+s.length();j++){
          q.push_back(p[j]);
       }
       pq.push(q);
       if(pq.size()>1) pq.pop();
    }
    return pq.top();
}
int main(){
    string s="cbabde";
    cout<<lexo_small(s);
}