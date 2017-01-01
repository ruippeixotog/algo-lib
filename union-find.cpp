/**
 * Union-Find structure
 *
 * Data structure that keeps track of a set of elements partitioned into a
 * number of disjoint (non-overlapping) subsets.
 *
 * Parameters:
 *   None.
 *
 * Operations:
 *   - `init(int n)` sets the initial state for `n` elements, where each one
 *     belongs to its own subset;
 *   - `get(int i)` returns the current subset of element `i`;
 *   - `join(int i, int j)` merges the subsets of elements `i` and `j`;
 *   - `sameSet(int i, int j)` returns if `i` and `j` belong to the same subset.
 *
 * Complexity:
 *   - Space: O(n);
 *   - Time:
 *       * `init`: O(n);
 *       * `get`: Amortized O(α(n)) ≈ O(1);
 *       * `join`: Amortized O(α(n)) ≈ O(1);
 *       * `sameSet`: Amortized O(α(n)) ≈ O(1).
 */

#define MAXN 1000

struct UnionFind {
  int pset[MAXN];
  int rank[MAXN];

  UnionFind() {}
  UnionFind(int n) {
    init(n);
  }

  void init(int n) { 
    for(int i = 0; i < n; i++) {
      pset[i] = i;
      rank[i] = 0; 
    }
  }

  int get(int i) {
    return (pset[i] == i) ? i : (pset[i] = get(pset[i]));
  }

  void join(int i, int j) {
    int xRoot = get(i);
    int yRoot = get(j);
    if (xRoot == yRoot) return;
    if (rank[xRoot] < rank[yRoot])
      pset[xRoot] = yRoot;
    else if (rank[xRoot] > rank[yRoot])
      pset[yRoot] = xRoot;
    else {
      pset[yRoot] = xRoot;
      rank[xRoot] = rank[xRoot] + 1;
    }
  }

  bool sameSet(int i, int j) {
    return get(i) == get(j);
  }
};

// -----------------------------------------------

#include <cassert>

int main() {
  int n = 5;
  UnionFind uf(n);

  for(int i = 0; i < n; i++)
    assert(uf.get(i) == i);

  uf.join(3, 4);
  assert(uf.get(3) == uf.get(4));
  assert(uf.get(3) == 4 || uf.get(4) == 3);

  uf.join(1, 4);
  assert(uf.sameSet(1, 3));
  assert(uf.get(1) == uf.get(3));

  return 0;
}
