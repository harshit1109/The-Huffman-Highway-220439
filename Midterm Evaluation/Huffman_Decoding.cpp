#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;
struct Node {
    char a;
    int data;
    Node *left, *right;
    Node(int data,char a) {
        this->a=a;
        this->data = data;
        this->left = this->right = NULL;
    }
    Node(int data, Node *left, Node *right) {
        a='\0';
        this->data = data;
        this->left = left;
        this->right = right;
    }
};
 
struct Comparison {
    bool operator() (Node*a, Node*b) {
    return a->data > b->data; // for min heap
}
};
 
class HuffmanTree
{
    vector<string> ans;
    void treeTraversal(Node *root, string s,map<string,char>&m) {
        if (!root) return;
        if (!root->left && !root->right) {
            ans.push_back(s);
            m[s]=root->a;
            return;
        }
        treeTraversal(root->left, s + "0",m);
        treeTraversal(root->right, s + "1",m);
    }  
public:
void huffmantree(string S,vector<int> f,int N,map<string,char>&mp)
{
    priority_queue<Node*, vector<Node*>, Comparison> pq;
    for (int i = 0; i < N; i++) {
        pq.push(new Node(f[i],S[i]));
    }
    while (pq.size() > 1) {
        Node *a = pq.top();
        pq.pop();
        Node *b = pq.top();
        pq.pop();
        Node *newNode = new Node(a->data + b->data, a, b);
        pq.push(newNode);
    }
    Node*treeroot = pq.top();
    treeTraversal(treeroot, "",mp);
}
};
string decode_file(string s,map<string,char>&mp){
       string a="";
       string ans="";
       for(int i=0;i<s.size();i++){
          a.push_back(s[i]);
          if(mp.find(a)!=mp.end()){ 
            ans.push_back(mp[a]);
            a="";
           }
       }
       return ans;
 }

string readFileAsString(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return "";
    }
    // Use a stringstream to read the file contents into a string
    stringstream buffer;
    buffer << inputFile.rdbuf();
    inputFile.close();
    return buffer.str();
}
int main(){
    //From Given frequency map
    string s="kjpxK.hcedyConaw gtrulisif,";

    vector<int>freq={2,1,8,1,1,3,7,4,17,7,2,1,16,8,6,1,29,6,14,7,6,4,5,5,1,2,1};

    HuffmanTree huff;

    Node* tree_root;
    map<string,char>mp;
    huff.huffmantree(s,freq,s.size(),mp);
    
    string filename="compressed.txt";
    string encoded=readFileAsString(filename);
    string decoded=decode_file(encoded,mp);
    cout<<decoded<<endl;
    string file_path = "decoded.txt";
    ofstream outFile(file_path);
    if (outFile.is_open()) {
        outFile << decoded;          
        outFile.close();             
    }             
    
}
