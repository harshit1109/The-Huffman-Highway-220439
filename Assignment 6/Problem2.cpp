#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
using namespace std;
bool dfs(int node, int curCount, int n, vector<int>& vis, vector<vector<int>>&adj){
        vis[node] = 1;
        curCount += 1;
        if(curCount == n){
            return true;
        }
        for(int i=0; i<adj[node].size(); i++){
            if(vis[adj[node][i]] == 0){
                if(dfs(adj[node][i], curCount, n, vis, adj)){
                    return true;
                }
            }
        }
        vis[node] = 0;
        return false;
    }
    bool check(int N,vector<vector<int>>adj)
    {
         vector<int> vis(N+1,0);
         for(int i=1; i<N+1; i++){
             if(vis[i] == 0){
                 if(dfs(i, 0, N, vis, adj)){
                     return true;
                 }
             }
         }
         return false;
    }
int main(){
    int v;
    cin>>v;
    vector<vector<int>>adj(v,vector<int>(v));
    vector<vector<int>>adj_list(v+1);
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
          cin>>adj[i][j];
          if(adj[i][j]==1) adj_list[i+1].push_back(j+1);
     }
    }
    cout<<check(v,adj_list);
}