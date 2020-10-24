#include <bits/stdc++.h>
using namespace std;

// square decomposition, count frequency of number k in some range
struct SD{
    const static int MAX = 1e5+5;
    int len, n;
    vector<vector<int>> cnt;
    vector<int> vals;
    SD(vector<int>& vals):vals(vals),n(vals.size()) {
        len = sqrt(vals.size()) + 1;
        cnt = vector<vector<int>>(len, vector<int>(MAX));
        for(int i=0;i<n;i++) cnt[i/len][vals[i]]++;
    }

    int query(int l, int r, int k) {
        int res = 0;
        int blockL = l/len, blockR = r/len;
        if(blockL == blockR) {
            for(int i=l;i<=r;i++) res += vals[i] == k;
        } else {
            for(int i=l;i<(blockL+1)*len;i++) res += vals[i] == k;
            for(int i=blockL+1;i<blockR;i++) res += cnt[i][k];
            for(int i=blockR*len;i<=r;i++) res += vals[i] == k;
        }
        return res;
    }
};

int main(){
    vector<int> test = {1, 2, 3, 3, 2, 1, 2};
    SD sd(test);
    cout << sd.query(0, 6, 2) << endl; // 3
    cout << sd.query(1, 5, 2) << endl; // 2
    cout << sd.query(0, 3, 2) << endl; // 1
    cout << sd.query(0, 6, 1) << endl; // 2
    cout << sd.query(3, 5, 3) << endl; // 1
    cout << sd.query(2, 3, 3) << endl; // 2
}
