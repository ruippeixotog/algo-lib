/**
 * Bipartite Matching
 *
 * Find the maximum number of edges between vertices of a bipartite graph so
 * that each vertex is covered by at most one edge.
 *
 * Parameters:
 *   - `m` (global): the number of vertices on one side;
 *   - `n` (global): the number of vertices on the other side;
 *   - `graph` (global): the adjacency matrix.
 *
 * Returns:
 *   - the function returns the number of matches;
 *   - `matchL` and `matchR` get filled with the matches for the two sides, or
 *     -1 when the vertex was left without a match.
 *
 * Complexity:
 *   O(m * n^2).
 */

#include <cstring>

#define MAXM 128
#define MAXN 128

int m, n;
bool graph[MAXM][MAXN];

bool seen[MAXN];
int matchL[MAXM], matchR[MAXN];

bool bpmDfs(int u) {
  for(int v = 0; v < n; v++) {
    if(graph[u][v]) {
      if(seen[v]) continue;
      seen[v] = true;

      if(matchR[v] < 0 || bpmDfs(matchR[v])) {
        matchL[u] = v; matchR[v] = u;
        return true;
      }
    }
  }
  return false;
}

int bpm() {
  memset(matchL, -1, sizeof(matchL));
  memset(matchR, -1, sizeof(matchR));
  int cnt = 0;
  for(int i = 0; i < m; i++) {
    memset(seen, false, sizeof(seen));
    if(bpmDfs(i)) cnt++;
  }
  return cnt;
}

// -----------------------------------------------

int main() {
  return 0;
}
