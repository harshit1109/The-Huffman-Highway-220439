#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
using namespace std;
void add_edge(int src,int des,vector<list<int>>&graph,bool bi_dir=true){
    graph[src].push_back(des);
    if(bi_dir){
        graph[des].push_back(src);
    }
}
void display(vector<list<int>>&graph){
    for(int i=0;i<graph.size();i++){
        cout<<i<<"->";
        for(auto ele:graph[i]){
            cout<<ele<<",";
        }
        cout<<endl;
    }
}
void dfs(int curr,int end,vector<list<int>>&undirected_graph,unordered_set<int>&isvisited,vector<vector<int>>&all_paths,vector<int>&paths){
    if(curr==end){
        paths.push_back(curr);
        all_paths.push_back(paths);
        paths.pop_back();
        return;
    }
    paths.push_back(curr);
    isvisited.insert(curr);
    for(auto neighbour:undirected_graph[curr]){
        if(isvisited.find(neighbour)==isvisited.end()){
          dfs(neighbour,end,undirected_graph,isvisited,all_paths,paths);
        }
    }
    isvisited.erase(curr);
    paths.pop_back();
}
void path(int src,int end,vector<list<int>>&undirected_graph,unordered_set<int>&isvisited,vector<vector<int>>&all_paths,vector<int>&paths){
    dfs(src,end,undirected_graph,isvisited,all_paths,paths);
}
int main(){
    int v;
    cin>>v;
    int e;
    cin>>e;
    vector<list<int>>undirected_graph(v);
    unordered_set<int>isvisited;
    vector<vector<int>>all_paths;
    vector<int>paths;
    while(e--){
        int s,d;
        cin>>s>>d;
        add_edge(s,d,undirected_graph);
    }
    int st,en;
    cin>>st>>en;
    path(st,en,undirected_graph,isvisited,all_paths,paths);
    for(auto ele:all_paths){
        for(auto i:ele){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}