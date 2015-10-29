#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

void bfs(int root, vector<vector<int> > &edges, vector<int> &minSum, vector<bool> &visited){
    list<int> queue;
    queue.push_back(root);
    visited[root-1] = true;
    
    while(!queue.empty()){
        int s = queue.front();
        
        queue.pop_front();
        vector<int> children = edges[s];
        for(int i=0;i<children.size();i++){
            int child = children[i];
            if(!visited[child-1]){
                queue.push_back(child);
                minSum[child-1] = minSum[s-1] + 6;
                visited[child-1] = true;
            }
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int t; cin>>t;
    int node1,node2;
    int n,m;
    
    while(t){
          
        //int node1,node2;
        cin>>n>>m; 
        
        vector<vector<int> > edges(n+1);
        
        for(int i=0;i<m;i++){
            
            cin >> node1;
            cin.ignore(1,' ');
            cin >> node2;            
            edges[node1].push_back(node2);
            edges[node2].push_back(node1);
        
        }
        
        int root; cin>>root;
        vector<int> minSum(n+1);
        vector<bool> visited(n+1);
        for(int i=0;i<n;i++){
            
            minSum[i] = 0;
            visited[i] = false;
        }
        
        bfs(root,edges,minSum,visited);
        for(int i=0;i<n;i++){
            if(i!=root-1) {
                if(minSum[i]==0){ cout<<-1<<" ";}
                else{ cout<<minSum[i]<<" ";}
            }
        }
        t--;
    }
    return 0;
}
