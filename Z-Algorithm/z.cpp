#include <bits/stdc++.h>
using namespace std;

// z_function is the number of characters ahead that is also the prefix starting from index i
vector<int> z_function(string s) {
    int n = s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main(){
    string s;
    cin >> s;
    for(auto z : z_function(s)) cout << z << " ";
}
