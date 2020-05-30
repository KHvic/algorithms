#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int p = 31; // some prime number for rolling hash
int mod = 1e9 + 9; // mod

// return all hash value of len k for some string s
set<ll> rolling_hash(string s, int k) {
    set<ll> res;
    // compute p^(k-1) for rolling hash
    ll power = 1;
    for(int i=0;i<k-1;i++) power = (power * p) % mod;

    ll s_hash = 0;
    for(int i=0;i<s.size();i++) {
        s_hash = (s_hash*p + s[i]) % mod;
        if(i>=k-1) {
            res.insert(s_hash);
            s_hash = (s_hash - (power*s[i-k+1]) + mod) % mod;
        }
    }
    return res;
}

// check if S is in T
// note we should also try to compress ascii value 'a' map to 1 to avoid possible overflow
vector<int> rabin_karp(string& s, string& t) {
    int S = s.size(), T = t.size();

    // compute all power of p
    vector<ll> p_pow(max(S, T));
    p_pow[0] = 1;
    for (int i = 1; i < p_pow.size(); i++)
        p_pow[i] = (p_pow[i-1] * p) % mod;

    // compute all hash prefix of T
    vector<ll> h(T + 1, 0);
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] * p_pow[i]) % mod) % mod;
    // compute full hash of S
    long long hash_s = 0;
    for (int i = 0; i < S; i++)
        hash_s = (hash_s + (s[i] * p_pow[i]) % mod) % mod;

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) {
        // get hash of substring in T, add mod because of negative possibility from %
        long long hash_t = (h[i+S] + mod - h[i]) % mod;
        if (hash_t == hash_s * p_pow[i] % mod) // check if hash match, mult power because of prefix length in t
            occurences.push_back(i);
    }
    return occurences;
}

int main()
{
    string sub = "eat";
    string str = "iloveatingeat";
    for(auto x : rabin_karp(sub , str))
        cout << x << endl;
    // should see that hash of sub is in str
    for(ll x : rolling_hash(str, sub.size()))
        cout << "rolling hash: " << x << endl;
    for(ll x : rolling_hash(sub, sub.size()))
        cout << "substring hash: " << x << endl;
}
