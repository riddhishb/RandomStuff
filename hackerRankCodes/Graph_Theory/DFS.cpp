/*
Atul is into graph theory, and he is learning about trees nowadays. He observed that the removal of an edge from a given tree T will result in the formation of two separate trees, T1 and T2.

Each vertex of the tree T is assigned a positive integer. Your task is to remove an edge, such that the Tree_diff of the resultant trees is minimized. Tree_diff is defined as the following: 
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int dfs(int root,vector<vector<int> >& edges,
       vector<int>& totSums,
       vector<int>& values,
       vector<bool>& visited){
    
    if(visited[root] == true){return 0;}
    
    if(edges[root].size() == 1){
        totSums[root] = values[root];
        visited[root] = true;
        return values[root];
    }
    
    vector<int> children = edges[root];
    int totalSum = 0;
    visited[root] = true;
    for(int i = 0;i < children.size();i++){
        int child = children[i];
        totalSum += dfs(child,
                       edges,
                       totSums,
                       values,
                       visited);
    }
    totalSum += values[root];
    totSums[root] = totalSum;
    
    return totalSum;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin>>N;
    vector<int> values(N+1);
    for(int i=1;i<N+1;i++){
        cin >> values[i];
    }
        
    vector<vector<int> > edges(N + 1);
    for(int i = 1;i <= N-1;i++){
        int node1,node2;
        cin>>node1>>node2;
        edges[node1].push_back(node2);
        edges[node2].push_back(node1);
    }
    
    int maxLen = 0;
    int root;
    for(int i = 1;i <= N;i++){
        if(edges[i].size() > maxLen){
            maxLen = edges[i].size();
            root = i;    
        }
    }
    
    vector<int> totSums(N+1);
    vector<bool> visited(N+1);
    for(int i = 1;i <= N;i++){
        totSums[i] = 0;
        visited[i] = false;
    }
    // DFS returns the total sum rooted at tree
    int s = dfs(root,edges,totSums,values,visited);
    
    int minDiff;
    int count = 0;
    for(int i = 1;i <= N ;i++){
        if(i != root){
            if(count == 0){
                minDiff = abs(s - 2*totSums[i]);
                count++;
            }else{
                int curDiff = abs(s - 2*totSums[i]);
                if(curDiff < minDiff)
                    minDiff = curDiff;
            }
        }
    }
    
    cout<<minDiff<<endl;
    return 0;
    
}

