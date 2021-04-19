#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unsigned mod_pow(unsigned a, unsigned b, unsigned mod) {
    unsigned result = 1;

    while (b > 0) {
        if (b & 1) result = unsigned(uint64_t(result) * a % mod);
        a = unsigned(uint64_t(a) * a % mod);
        b >>= 1;
    }

    return result;
}

bool miller_rabin(unsigned n) {
    if (n < 2)
        return false;

    // Check small primes.
    for (unsigned p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29})
        if (n % p == 0)
            return n == p;

    int r = __builtin_ctz(n - 1);
    unsigned d = (n - 1) >> r;

    // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
    for (unsigned a : {2, 7, 61}) {
        unsigned x = mod_pow(a % n, d, n);

        if (x <= 1 || x == n - 1)
            continue;

        for (int i = 0; i < r - 1 && x != n - 1; i++)
            x = unsigned(ll(x) * x % n);

        if (x != n - 1)
            return false;
    }

    return true;
}

int main(){
    for(int i=0;i<100;i++)
        if(miller_rabin(i))
            cout << i << endl;
}
