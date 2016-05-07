#include <vector>

#define MOD 1000000007

using namespace std;

typedef long long ll;

inline ll mmul(ll a, ll b) { return (a * b) % MOD; }
inline ll madd(ll a, ll b) { return (a + b) % MOD; }

ll mpow(ll a, ll p) {
  if(p == 0) return 1;
  ll halfPow = mpow(a, p / 2);
  return mmul(halfPow, p % 2 ? mmul(a, halfPow) : halfPow);
}

// modular inverse exists only if MOD is prime (or coprime to a)
ll minv(ll a) { return mpow(a, MOD - 2); }
ll mdiv(ll a, ll b) { return mmul(a, minv(b)); }

vector<ll> _mfactMem(1, 1);
ll mfact(ll a) {
  if(a >= MOD) return 0;
  while(a >= _mfactMem.size())
    _mfactMem.push_back(mmul(_mfactMem.size(), _mfactMem.back()));
  return _mfactMem[a];
}

ll mcomb(ll n, ll k) {
  if (n == 0 && k == 0) return 1;
  ll ni = n % MOD, ki = k % MOD;
  if (ni < ki) return 0;
  ll comb = mmul(mfact(ni), mmul(minv(mfact(ki)), minv(mfact(ni - ki))));
  return mcomb(n / MOD, k / MOD) * comb;
}

// -----------------------------------------------

#include <cstdio>

int main() {
  fprintf(stderr, "2^2 = %lld\n", mpow(2, 2));
  fprintf(stderr, "2^3 = %lld\n", mpow(2, 3));
  fprintf(stderr, "2^4 = %lld\n", mpow(2, 4));
  fprintf(stderr, "3^3 = %lld\n", mpow(3, 3));

  fprintf(stderr, "10 / 2 = %lld\n", mdiv(10, 2));
  fprintf(stderr, "12 / 4 = %lld\n", mdiv(12, 4));
  fprintf(stderr, "246824682468 / 123412341234 = %lld\n",
          mdiv(246824682468 % MOD, 123412341234 % MOD));

  fprintf(stderr, "3! = %lld\n", mfact(3));
  fprintf(stderr, "4! = %lld\n", mfact(4));
  fprintf(stderr, "5! = %lld\n", mfact(5));
  fprintf(stderr, "6! = %lld\n", mfact(6));
  fprintf(stderr, "12! = %lld\n", mfact(12));
  fprintf(stderr, "13! = %lld\n", mfact(13));

  fprintf(stderr, "4C0 = %lld\n", mcomb(4, 0));
  fprintf(stderr, "4C1 = %lld\n", mcomb(4, 1));
  fprintf(stderr, "4C2 = %lld\n", mcomb(4, 2));
  fprintf(stderr, "4C3 = %lld\n", mcomb(4, 3));
  fprintf(stderr, "4C4 = %lld\n", mcomb(4, 4));

  return 0;
}
