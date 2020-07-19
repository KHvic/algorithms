#include<bits/stdc++.h>
using namespace std;

const int MAXN = 3*1e5 + 10;
const int MAXP = log2(MAXN) + 10;
int min_table[MAXP][MAXN];
int a[MAXN];
int numlog[MAXN];
int n;


void init() {
    numlog[1] = 0;
    for(int i=2;i<=n;i++) numlog[i] = numlog[i/2] + 1;

    for(int i=0;i<=numlog[n];i++) {
        int skiprange = 1<<i;
        for(int j=0;j+skiprange<=n;j++) {
            if(i==0) {
                min_table[i][j] = a[j];
                continue;
            }
            min_table[i][j] = min(min_table[i-1][j], min_table[i-1][j+(skiprange>>1)]);
        }
    }
}

int query(int low, int high) {
    int range = high-low+1;
    int p = numlog[range];
    int mn = min(min_table[p][low], min_table[p][high-(1<<p)+1]);
    return mn;
}


int main() {
    vector<int> tmp = {4,3,2,1};
    n = tmp.size();
    copy(tmp.begin(), tmp.end(), a);
    init();
    cout << query(0, 3) << "\n"; // 1
    cout << query(0, 1) << "\n"; // 3
    cout << query(1, 2) << "\n"; // 2
}
