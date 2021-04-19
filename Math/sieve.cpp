#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//O((range)loglog(R)+√Rloglog√R)
vector<ll> segmentedSieve(ll L, ll R) {
    // generate all primes up to sqrt(R)
    ll lim = sqrt(R);
    vector<bool> mark(lim + 1, false);
    vector<ll> primes;
    for (ll i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (ll j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<bool> isPrime(R - L + 1, true);
    for (ll i : primes)
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;

    vector<ll> res;
    for(int i=0;i<R-L+1;i++)
        if(isPrime[i])
            res.push_back(i+L);

    return res;
}

int main(){
    segmentedSieve(50, 999);
}
