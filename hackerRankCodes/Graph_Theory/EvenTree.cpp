/*
You are given a tree (a simple connected graph with no cycles). You have to remove as many edges from the tree as possible to obtain a forest with the condition that : Each connected component of the forest should contain an even number of vertices.

To accomplish this, you will remove some edges from the tree. Find out the number of removed edges.

The first line of input contains two integers N and M. N is the number of vertices and M is the number of edges. 
The next M lines contain two integers ui and vi which specifies an edge of the tree. (1-based index)
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

int num_of_nodes(int root, vector<vector<int> > edges,int n){
    // normal BFS implementation to find the number of nodes in the tree
    vector<bool > vis(n+1);
    for(int i=0;i<=n;i++) vis[i] =false;
    list<int> queue;
    vis[root-1] = true;
    int count = 1;
    queue.push_back(root);
    
    while(!queue.empty()){
        int k = queue.front();
        queue.pop_front();
        
        vector<int> children = edges[k];
        for(int j=0;j<children.size();j++){
            int child = children[j];
            if(!vis[child-1]){ vis[child-1] = true;
                                 count++;
                                  queue.push_back(child);
                                 }
        }
    }
    return count;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n,m;
    cin>>n>>m;
    int node1,node2;
    vector<vector<int> > edges(n+1);
    //vector<vector<int> > edges_temp(n+1);
    for(int i=0;i<m;i++){
        cin>>node1>>node2;
        edges[node1].push_back(node2);
        edges[node2].push_back(node1);
    }
    vector<bool > visited(n+1);
    int ans = 0;
    for(int i=0;i<=n;i++) visited[i] = false;
    //cout <<edges[1].size();
    for(int i=1;i<=n;i++){
       
        for(int j=0;j<edges[i].size();j++){
            
            
                int s = edges[i].front();
            if(!visited[s]){
               // cout <<s<<endl;
                edges[i].erase(std::find(edges[i].begin(),edges[i].end(),s));
                edges[s].erase(std::find(edges[s].begin(),edges[s].end(),i));
      
                if(num_of_nodes(i,edges,n)%2 ==0 && num_of_nodes(s,edges,n)%2==0){ans++;}
                edges[i].push_back(s);
                edges[s].push_back(i);
      
            }
        }
        
        visited[i] = true;
    }
    
    cout<<ans <<endl;
    return 0;
}

