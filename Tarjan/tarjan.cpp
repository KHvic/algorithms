#include <bits/stdc++.h>
using namespace std;

struct Tarjan {
    vector<vector<int>> graph;
    vector<int> represent, low, idx, st;
    vector<bool> instack;
    int numSCC;
    int n, cur;

    Tarjan(int N): n(N), numSCC(0) {
        graph = vector<vector<int>>(n);
    }

    void dfs(int v) {
        low[v] = idx[v] = ++cur;
        st.push_back(v);
        instack[v] = true;
        for(int out : graph[v]) {
            if(!idx[out]) dfs(out);
            if(instack[out]) low[v] = min(low[v], low[out]);
        }
        if(low[v] == idx[v]) {
            numSCC++;
            while(1) {
                int top = st.back(); st.pop_back();
                instack[top] = false;
                represent[top] = v;
                if(top == v) break;
            }
        }
    }

    int start() {
        st.clear();
        represent = low = idx = vector<int>(n);
        instack = vector<bool>(n);
        numSCC = 0, cur = 0;
        for(int i=0;i<n;i++)
            if(!idx[i])
                dfs(i);
        return numSCC;
    }

    void addEdge(int a, int b) {
        graph[a].push_back(b);
    }
};

int main() {
    // expect 3 SCC from this graph
    Tarjan tarjan(6);
    vector<vector<int>> edges = {{0,1},{1,2},{2,4},{4,5},{5,4},{3,1},{2,3}};
    for(auto& edge : edges) tarjan.addEdge(edge[0], edge[1]);

    tarjan.start();
    printf("Number of SCC: %d\n", tarjan.numSCC);
    for(int i=0; i<tarjan.n; i++) {
        printf("Node %d, representative node %d\n", i, tarjan.represent[i]);
    }
}
