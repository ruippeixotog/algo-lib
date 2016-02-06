/**
 * Hungarian algorithm (Kuhn–Munkres algorithm)
 *
 * Finds a minimum weight perfect matching in a weighted bipartite graph.
 * Equivalently, finds a minimum cost assignment between `n` workers and `n`
 * jobs.
 *
 * Parameters:
 *   - `w` (global): the weight of using the edge going from i to j;
 *   - `n`: the number of matches to make.
 *
 * Returns:
 *   - the function returns the total weight of the minimum weight assignment;
 *   - `mx` is filled with the assignment of i.
 *
 * Complexity:
 *   O(n^3).
 */

#include <algorithm>
#include <cstring>

#define MAXN 1000
#define INF 1e9

using namespace std;

int w[MAXN][MAXN], s[MAXN], rem[MAXN], remx[MAXN];
int mx[MAXN], my[MAXN], lx[MAXN], ly[MAXN];

void kuhnAdd(int x, int n) {
  s[x] = true;
  for(int y = 0; y < n; y++)
    if(rem[y] != -INF && rem[y] > lx[x] + ly[y] - w[x][y])
      rem[y] = lx[x] + ly[y] - w[x][y], remx[y] = x;
}

int kuhnMunkres(int n) {
  for(int i = 0; i < n; i++) {
    mx[i] = my[i] = -1;
    lx[i] = ly[i] = 0;
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++)
      ly[j] = max(ly[j], w[i][j]);
  }
  for(int i = 0; i < n; i++) {
    memset(s, 0, sizeof(s));
    memset(rem, 0x3f, sizeof(rem));

    int st;
    for(st = 0; st < n; st++) {
      if(mx[st] == -1) { kuhnAdd(st, n); break; }
    }
    while(mx[st] == -1) {
      int miny = -1;
      for(int y = 0; y < n; y++) {
        if(rem[y] != -INF && (miny == -1 || rem[miny] >= rem[y]))
          miny = y;
      }

      if(rem[miny]) {
        for(int x = 0; x < n; x++) if(s[x]) lx[x] -= rem[miny];
        for(int y = 0, d = rem[miny]; y < n; y++) {
          if(rem[y] == -INF) ly[y] += d;
          else rem[y] -= d;
        }
      }

      if(my[miny] == -1) {
        int cur = miny;
        while(remx[cur] != st) {
          int pmate = mx[remx[cur]];
          my[cur] = remx[cur]; mx[my[cur]] = cur;
          my[pmate] = -1; cur = pmate;
        }
        my[cur] = remx[cur]; mx[my[cur]] = cur;
      } else {
        kuhnAdd(my[miny], n); rem[miny] = -INF;
      }
    }
  }

  int ret = 0;
  for(int i = 0; i < n; i++)
    ret += w[i][mx[i]];
  return ret;
}

// -----------------------------------------------

int main() {
  return 0;
}
