// code for finding the strongly connected components for a directed graph

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

void dfs_gt(int u,vector<vector<int> > &edges,vector<bool> &vis){
	
	vis[u] = true;
	cout<<u<<" ";
	vector<int> children = edges[u];
	for(int i=0;i<children.size();i++){
		int child = children[i];
		
		if(!vis[child]){

			dfs_gt(child,edges,vis);

		}
	}

}

void dfs_g(int u,vector<vector<int> > &edges,vector<bool> &vis, stack<int> &stk){
	
	vis[u] = true;

	vector<int> children = edges[u];
	for(int i=0;i<children.size();i++){
		int child = children[i];
		
		if(!vis[child]){

			dfs_g(child,edges,vis,stk);

		}
	}
	stk.push(u);
}

int main(){
	int n,m;
	int node1,node2;
	cin>>n>>m;
	vector<vector<int> > edgesg(n+1);
	vector<vector<int> > edgesgt(n+1);

	// constructing the forward and the transpose of the graph
	for(int i=0;i<m;i++){
		cin>>node1>>node2;
		edgesg[node1].push_back(node2);
		edgesgt[node2].push_back(node1);
	}
	vector<bool> vis(n+1);
	stack<int> stk;
	for(int i = 0;i<n+1;i++) vis[i] = false;

	for(int i=1;i<n+1;i++){
		if(!vis[i]){
			dfs_g(i,edgesg,vis,stk);
		}
	}	

	for(int i = 0;i<n+1;i++) vis[i] = false;

	while(!stk.empty()){
		int v = stk.top();
		stk.pop();
		if(!vis[v]){
			dfs_gt(v,edgesgt,vis);
			cout<<endl;
		}
	}	
}