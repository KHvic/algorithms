#include <bits/stdc++.h>
using namespace std;

struct Kosaraju {
    vector<vector<int>> graph, rgraph;
    vector<int> represent;
    vector<bool> visited;
    stack<int> topdown;
    int numSCC;
    int n;

    Kosaraju(int N): n(N) {
        graph = rgraph = vector<vector<int>>(n);
    }

    void dfs1(int idx) {
        if(visited[idx]) return;
        visited[idx] = true;
        for(int next : graph[idx]) dfs1(next);
        topdown.push(idx);
    }

    void dfs2(int idx, int rep) {
        if(visited[idx]) return;
        visited[idx] = true;
        represent[idx] = rep;
        for(int next : rgraph[idx]) dfs2(next, rep);
    }

    int start() {
        numSCC = 0;
        represent = vector<int>(n);
        visited = vector<bool>(n);
        // step1: do dfs on normal graph to get stack topdown ordering
        for(int i=0;i<n;i++) dfs1(i);

        // step2: find representative for each node using reverse graph and topdown stack
        visited.assign(n, false);
        while(!topdown.empty()) {
            int cur = topdown.top(); topdown.pop();
            if(visited[cur]) continue;
            dfs2(cur, cur);
            numSCC++;
        }
        return numSCC;
    }

    void addEdge(int a, int b) {
        graph[a].push_back(b);
        rgraph[b].push_back(a);
    }
};

int main() {
    // expect 3 SCC from this graph
    Kosaraju ko(6);
    vector<vector<int>> edges = {{0,1},{1,2},{2,4},{4,5},{5,4},{3,1},{2,3}};
    for(auto& edge : edges) ko.addEdge(edge[0], edge[1]);

    ko.start();
    printf("Number of SCC: %d\n", ko.numSCC);
    for(int i=0; i<ko.n; i++) {
        printf("Node %d, representative node %d\n", i, ko.represent[i]);
    }
}
