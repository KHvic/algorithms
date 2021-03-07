#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// return g = a*x + y*b, compute linear diophantine solution
ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

// r ≡ a % m
// r ≡ b % n
// r = a + n*x = b + m*y for some x & y (linear diophantine)
// b - a = n*x - m*y
// exist a solution if gcd g divides (b-a)
// x = (b-a)/g*x', y = (b-a)/g*y' where x' & y' are result from extended euclid
// r = a + n*(b-a)/g*x', by substituting x
ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if((a-b) % g != 0) return -1; // no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}

// extended euclidean way to find modular inverse
// call invEuclid(x, mod);
ll invEuclid(ll a, ll b){
    return 1<a ? b - invEuclid(b%a,a)*b/a : 1;
}

int main() {
    // Given
    // x ≡ 3 (mod 5)
    // x ≡ 1 (mod 7)
    // x ≡ 6 (mod 8)
    // compute smallest possible x
    ll first2 = crt(3, 5, 1, 7);
    ll lcm2 = 5*7/__gcd(5, 7);
    ll solution = crt(first2, lcm2, 6, 8);
    cout << solution; // 78
}
