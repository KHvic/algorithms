#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n = 5;
deque<int> eulerCircuit;
map<int, multiset<int>> graph;

bool canVisitAll(int start) {
    queue<int> bfs;
    set<int> visited;
    visited.insert(start);
    bfs.push(start);
    while(!bfs.empty()) {
        int cur = bfs.front(); bfs.pop();
        for(int next : graph[cur])
            if(!visited.count(next)) {
                visited.insert(next);
                bfs.push(next);
            }
    }
    return visited.size() == n;
}

// check if graph is euler circuit
bool isEulerCircuit() {
    // two condition for euler circuit
    // 1. can visit all nodes from any
    // 2. all nodes' indegree = outdegree
    if(!canVisitAll(0)) return false;
    map<int,int> indegree;
    map<int,int> outdegree;
    for(auto edges : graph) {
        for(auto next : edges.second) {
            indegree[next]++;
        }
    }
    for(auto out: outdegree) {
        int x = out.first;
        if(out.second != indegree[x]) return false;
    }
    return true;
}

// what about euler path?
// two condition for euler path
// condition 1:
// the starting node has outdegree - indegree = 1
// the ending node has indegree - outdegree = -1
// all the other node has indegree = outdegree
// condition 2:
// starting node can reach all other nodes

// main algorithm of hierholzer is to visit until we can't do so anymore
// then trace back and visit some other paths in between
void hierholzer(int cur) {
    while(graph[cur].size()) {
        int next = *graph[cur].begin();
        graph[cur].erase(graph[cur].begin());
        hierholzer(next);
    }
    eulerCircuit.push_front(cur);
}

void findEulerCircuit(vector<vector<int>>& edges) {
    eulerCircuit.clear();
    graph.clear();
    for(auto edge : edges)
        graph[edge[0]].insert(edge[1]);
    cout << (isEulerCircuit() ? "is euler curcuit" : "not euler curcuit") << endl;
    // anyone start node will do in euler circuit
    // for euler path, we need to find the starting node with outdegree-indegree = 1
    hierholzer(0);
}

int main() {
    vector<vector<int>> edges = {{0,1},{1,2},{1,3},{2,1},{3,4},{4,0}};
    findEulerCircuit(edges);
    for(auto x : eulerCircuit)
        printf("%d ", x);
}
