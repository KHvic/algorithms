#include<bits/stdc++.h>
using namespace std;

class FT {
private: vector<int> ft;
public:
    FT(int n) {
        ft.assign(n + 1, 0);
    }
    FT(vector<int>& vals): FT(vals.size()) {
        for (int i=0; i<vals.size(); i++) adjust(i, vals[i]);
    }
    int rsq(int b) {
        int sum = 0;
        for (b++; b; b -= (b&-b)) sum += ft[b];
        return sum;
    }
    int rsq(int a, int b) {
        return rsq(b) - rsq(a-1);
    }
    void adjust(int k, int v) {
        for (k++; k<ft.size(); k += (k&-k)) ft[k] += v;
    }
};

int main()
{
    vector<int> test = {2, 5, 1, 7};
    FT ft(test);
    cout << ft.rsq(3) << "\n"; // 15
    cout << ft.rsq(1, 2) << "\n"; // 6
    ft.adjust(1, -3);
    cout << ft.rsq(1, 2) << "\n"; // 3
}
