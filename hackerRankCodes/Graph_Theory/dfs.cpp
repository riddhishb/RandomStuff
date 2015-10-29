// DFS Again

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <climits>

using namespace std;


void dfs(int u,vector<vector<int> > &edges,vector<bool> &vis, vector<int> &parent){
	cout<<u<<endl;
	vis[u] = true;

	vector<int> children = edges[u];
	for(int i=0;i<children.size();i++){
		int child = children[i];
		
		if(!vis[child]){
			parent[child] = u;			
			dfs(child,edges,vis,parent);

	}
}
}
int main(){
	int n,m,node1,node2;
	// input the number of nodes and edges
	cin>>n>>m;
	vector<vector<int> > edges(n+1);
	for(int i=0;i<m;i++){
		cin>>node1>>node2;
		edges[node1].push_back(node2);
		edges[node2].push_back(node1);
	}
	int maxLen = 0;
    int root;
    for(int i = 1;i <= n;i++){
        if(edges[i].size() > maxLen){
            maxLen = edges[i].size();
            root = i;    
        }
    }
    vector<bool> vis(n+1);
    vector<int> parent(n+1);
    for(int i=0;i<n;i++){
    	vis[i] = false;
    	parent[i] = -1;
    }
	for(int i=1;i<=n;i++){
		if(!vis[i]){
    
			dfs(i,edges,vis,parent);
		}
	}

return 0;
}
