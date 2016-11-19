/*
 * Miller–Rabin primality test
 *
 * Performs a randomized test for the primality of a number. False positives
 * can occur - hence, it can only declare a number as _probably_ prime. On the
 * other hand, false negatives cannot happen.
 *
 * The accuracy is controlled by the number of random bases to test. In general,
 * if the given number is composite this test declares it probably prime with a
 * probability of at most 1 / 4^(bases). The probablity can be smaller depending
 * on the density of the prime numbers near the number to test.
 *
 * Parameters:
 *   - `n`: the number to test for primality;
 *   - `bases`: the number of random bases to test.
 *
 * Returns:
 *   - the function returns `true` if the number is probably prime and `false`
 *     if it is surely composite.
 *
 * Complexity:
 *   O(bases * log(n)).
 */

#include <cstdlib>

typedef long long ll;

inline ll mmul(ll a, ll b, ll mod) { return (a * b) % mod; }

ll mpow(ll a, ll p, ll mod) {
  if(p == 0) return 1;
  ll halfPow = mpow(a, p / 2, mod);
  return mmul(halfPow, p % 2 ? mmul(a, halfPow, mod) : halfPow, mod);
}

ll randBetween(ll a, ll b) {
  ll r = ((ll)(rand() & ~(1 << 31)) << 32) | rand();
  return a + r % (b - a + 1);
}

bool isPrime(ll n, int bases = 10) {
  if (n == 2 || n == 3) return true;
  if (n <= 1 || n % 2 == 0) return false;

  // Write (n - 1) as (d * 2^s) by factoring powers of 2 from (n - 1)
  int s = 0;
  for (ll m = n - 1; m % 2 == 0; ++s, m /= 2);
  ll d = (n - 1) / (1 << s);

  for(int i = 0; i < bases; i++) {
    ll a = randBetween(2, n - 2);
    ll x = mpow(a, d, n);

    if (x == 1 || x == n - 1)
      continue;

    bool found = false;
    for(int r = 1; r <= s - 1; r++) {
      x = mpow(x, 2, n);
      if(x == 1) return false;
      if(x == n - 1) { found = true; break; }
    }
    if(!found) return false;
  }
  return true;
}

// -----------------------------------------------

#include <cstdio>
#include <ctime>

int main() {
  srand(time(NULL));

  printf("2 is prime: %d (expected 1)\n", isPrime(2));
  printf("3 is prime: %d (expected 1)\n", isPrime(3));
  printf("4 is prime: %d (expected 0)\n", isPrime(4));
  printf("5 is prime: %d (expected 1)\n", isPrime(5));

  printf("45896223 is prime: %d (expected 0)\n", isPrime(45896223));
  printf("219567251 is prime: %d (expected 1)\n", isPrime(219567251));
  printf("213587648531 is prime: %d (expected 0)\n", isPrime(213587648531L));
  printf("3000011921 is prime: %d (expected 1)\n", isPrime(3000011921L));

  return 0;
}
