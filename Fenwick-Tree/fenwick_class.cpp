#include<bits/stdc++.h>
using namespace std;

class FenwickTree {
private: vector<int> ft;
public:
    FenwickTree(int n) {
        ft.assign(n + 1, 0);
    }
    int rsq(int b) {
        b++;
        int sum = 0;
        for (; b; b -= (b&-b)) sum += ft[b];
        return sum;
    }
    int rsq(int a, int b) {
        return rsq(b) - rsq(a-1);
    }
    void adjust(int k, int v) {
        k++;
        for (; k < (int)ft.size(); k += (k&-k)) ft[k] += v;
    }
};

int main()
{
    int f[] = { 0,2,4,5,5,6,6,6,7,7,8,9 }; // m = 11 scores
    FenwickTree ft(11); // declare a Fenwick Tree for range [0..11]
    // insert these scores manually one by one into an empty Fenwick Tree
    for (int i = 0; i < 11; i++) ft.adjust(f[i], 1); // this is O(k log n)
    printf("%d\n", ft.rsq(0, 2)); // 2
    printf("%d\n", ft.rsq(1, 1)); // 0 => ft[1] = 0
    printf("%d\n", ft.rsq(1, 2)); // 1 => ft[2] = 1
    printf("%d\n", ft.rsq(1, 6)); // 7 => ft[6] + ft[4] = 5 + 2 = 7
    printf("%d\n", ft.rsq(1, 10)); // 11 => ft[10] + ft[8] = 1 + 10 = 11
    printf("%d\n", ft.rsq(3, 6)); // 6 => rsq(1, 6) - rsq(1, 2) = 7 - 1
    ft.adjust(5, 2); // update demo
    printf("%d\n", ft.rsq(1, 10)); // now 13
}
