#include <bits/stdc++.h>
using namespace std;

unordered_map<int,vector<int>> graph;
unordered_map<int,vector<int>> rgraph;
unordered_set<int> visited;
stack<int> topdown;
unordered_map<int,int> represent;
int numSCC = 0;
int n;

void dfs1(int idx) {
    if(visited.count(idx)) return;
    visited.insert(idx);
    for(int next : graph[idx])
        dfs1(next);
    topdown.push(idx);
}

void dfs2(int idx, int rep) {
    if(visited.count(idx)) return;
    visited.insert(idx);
    represent[idx] = rep;
    for(int next : rgraph[idx])
        dfs2(next, rep);
}

void kosaraju() {
    // step1: do dfs on normal graph to get stack topdown ordering
    for(int i=0;i<n;i++) {
        dfs1(i);
    }
    visited.clear();
    // step2: find representative for each node using reverse graph and topdown stack
    while(!topdown.empty()) {
        int cur = topdown.top(); topdown.pop();
        if(visited.count(cur)) continue;
        dfs2(cur, cur);
        numSCC++;
    }
}

void constructGraph(vector<vector<int>>& edges, int s) {
    n = s;
    for(auto edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        rgraph[edge[1]].push_back(edge[0]);
    }
}

int main() {
    // expect 3 SCC from this graph
    vector<vector<int>> edges = {{0,1},{1,2},{2,4},{4,5},{5,4},{3,1},{2,3}};
    constructGraph(edges, 6);
    kosaraju();
    printf("Number of SCC: %d\n", numSCC);
    for(auto p : represent) {
        printf("Node %d, representative node %d\n", p.first, p.second);
    }
}
