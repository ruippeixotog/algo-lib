/**
 * Knuth-Morris-Pratt algorithm
 *
 * Searches for occurrences of `pattern` within `str`, keeping information of
 * where the next match could begin when a mismatch occurs.
 *
 * Parameters:
 *   - `str`: the string to search;
 *   - `pattern`: the pattern to find in the string;
 *   - `res`: the vector to be filled with the results.
 *
 * Returns:
 *   - `res` is filled with the starting indices of all the (possibly
 *     overlapping) matches.
 *
 * Complexity:
 *   O(n + k), with `n == str.length()` and `k == pattern.length()`.
 */

#include <string>
#include <vector>

#define MAXN 2000

using namespace std;

int pi[MAXN];

void kmp(string str, string pattern, vector<int>& res) {
  res.clear();

  pi[0] = 0;
  for(int i = 1; i < pattern.size(); i++) {
    pi[i] = pi[i - 1];
    while(pi[i] > 0 && pattern[i] != pattern[pi[i]])
      pi[i] = pi[pi[i] - 1];
    if(pattern[i] == pattern[pi[i]]) pi[i]++;
  }

  int k = 0;
  for(int i = 0; i < str.size(); i++) {
    while(k > 0 && str[i] != pattern[k])
      k = pi[k - 1];
    if(str[i] == pattern[k]) k++;
    if(k == pattern.size()) {
      res.push_back(i - k + 1);
      k = pi[k - 1];
    }
  }
}

// -----------------------------------------------

#include <iostream>

int main() {
  vector<int> res;
  kmp("AABAACAADAABAAABAA", "AABA", res);

  cout << "Expected: 0 9 13" << endl;
  cout << "  Result: ";
  for(int idx : res) cout << idx << " ";
  cout << endl;
  return 0;
}
