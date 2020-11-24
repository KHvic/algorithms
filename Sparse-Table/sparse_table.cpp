#include<bits/stdc++.h>
using namespace std;

struct RMQ {
    int n;
    vector<int> numlog;
    vector<vector<int>> min_table;
    RMQ(vector<int>& vals):n(vals.size()) {
        numlog = vector<int>(n+1);
        numlog[1] = 0;
        for(int i=2;i<=n;i++) numlog[i] = numlog[i/2] + 1;

        min_table = vector<vector<int>>(numlog[n]+1, vector<int>(n+1));
        for(int i=0;i<=numlog[n];i++) {
            int skiprange = 1<<i;
            for(int j=0;j+skiprange<=n;j++) {
                if(i==0) {
                    min_table[i][j] = vals[j];
                    continue;
                }
                min_table[i][j] = operate(min_table[i-1][j], min_table[i-1][j+(skiprange>>1)]);
            }
        }
    }

    int query(int low, int high) {
        int range = high-low+1;
        int p = numlog[range];
        int mn = operate(min_table[p][low], min_table[p][high-(1<<p)+1]);
        return mn;
    }

    int operate(int a, int b) {
        return min(a, b);
    }
};


int main() {
    vector<int> tmp = {4,3,2,1};
    RMQ rmq(tmp);
    cout << rmq.query(0, 3) << "\n"; // 1
    cout << rmq.query(0, 1) << "\n"; // 3
    cout << rmq.query(1, 2) << "\n"; // 2
}
