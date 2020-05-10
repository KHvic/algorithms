#include <bits/stdc++.h>
using namespace std;

#define NIL 0
#define INF INT_MAX
#define MAXM 100
#define MAXN 100

// alternating path is a path that starts and ends on free nodes & alternating between unmatched and matched edges
// intuition: the length of augmenting paths cannot become shorter, it always increase by 1 after each dfs augmentation

int m, n; // set number of vertices on left and right sides of bipartite graph

list<int> *adj; // add edges before calling the algorithm

int pairU[MAXM], pairV[MAXN], dist[MAXM];

void addEdge(int u, int v) {
    adj[u].push_back(v);
}

// Returns true if there is an augmenting path beginning with free vertex u
bool dfs(int u) {
    if (u == NIL)
        return true;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (dist[pairV[v]] == dist[u] + 1) {
            if (dfs(pairV[v])) {
                // include pairing in graph
                // note*: at the same time, we also overwrite any pre-existing pairing of pairV[v]
                pairV[v] = u;
                pairU[u] = v;
                return true;
            }
        }
    }
    dist[u] = INF; // mark used
    return false;
}

// Returns true if there is an augmenting path, else returns false
bool bfs() {
    queue<int> q;
    // go thru all nodes on left
    for (int u = 1; u <= m; ++u) {
        // add free nodes not part of existing matching pairs as source of bfs
        if (pairU[u] == NIL) {
            dist[u] = 0;
            q.push(u);
        } else
            dist[u] = INF; // mark non-free matched nodes as INF
    }
    dist[NIL] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // if is free node
        if (dist[u] < dist[NIL]) {
            list<int>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = *i; // right node
                // find matching left nodes connected to adjacent right node
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    // as all free nodes are paired with NIL
    // this indicate able to reach some free node then augment path exist
    return (dist[NIL] != INF);
}


// O(sqrt(V)*E)
// compute maximum matching of a bipartite graph
int hopcraftKarp() {
    for (int i = 0; i <= m; i++)
        pairU[i] = NIL;
    for (int i = 0; i <= n; i++)
        pairV[i] = NIL;
    int matching = 0;
    // while there is a alternating node
    while (bfs()) {
        for (int i = 1; i <= m; i++)
            if (dfs(i))
                ++matching; // each success augmentation increase pairing by 1
    }
    return matching;
}


int main() {
    m = n = 4;
    adj = new list<int>[m + 1];
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 1);
    addEdge(3, 2);
    addEdge(4, 2);
    addEdge(4, 4);
    cout << "maximum matching of the bipartite graph is: ";
    cout << hopcraftKarp() << endl;

    return 0;
}
