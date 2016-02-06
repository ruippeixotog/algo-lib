/**
 * Edmonds-Karp relabelling with a modified Dijkstra
 *
 * Takes a directed graph where each edge has a capacity and a cost per unit of
 * flow and returns a maximum flow network of minimal cost from a source to a
 * sink vertex.
 *
 * Parameters:
 *   - `n` (global): the number of vertices;
 *   - `adjs` (global): the adjacency list of the graph;
 *   - `cost` (global): the cost per unit of flow from i to j;
 *   - `cap` (global): the capacity of the edge from i to j;
 *   - `src`: the source vertex;
 *   - `sink`: the sink vertex.
 *
 * Returns:
 *   - the function returns a pair containing the minimum cost and the maximum
 *     flow, in this order;
 *   - `flow` is filled with the minimum cost flow network.
 *
 * Complexity:
 *   O((e + n*log(n)) * maxFlow), where `e` is the number of edges.
 */

#include <algorithm>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

#define MAXN 1000
#define INF 1e9

using namespace std;

int n;
vector<int> adjs[MAXN];
int cost[MAXN][MAXN], cap[MAXN][MAXN];

int dist[MAXN], parent[MAXN], pi[MAXN];  // shortest path
int flow[MAXN][MAXN];                    // mcmf

inline int pot(int u, int v) { return dist[u] + pi[u] - pi[v]; }

int dijkstra(int src, int dest) {
  memset(dist, 0x3f, sizeof(dist));
  memset(parent, -1, sizeof(parent));

  priority_queue<pair<int, int>> q;
  q.push(make_pair(0, src)); dist[src] = 0;

  while(!q.empty()) {
    int curr = q.top().second; q.pop();

    if(parent[curr] >= 0) continue;
    parent[curr] = -parent[curr] - 1;

    for(int adj : adjs[curr]) {
      if(parent[adj] >= 0) continue;

      if(flow[adj][curr] && pot(curr, adj) - cost[adj][curr] < dist[adj]) {
        dist[adj] = pot(curr, adj) - cost[adj][curr];
        parent[adj] = -curr - 1;
        q.push(make_pair(-dist[adj], adj));
      }

      if(flow[curr][adj] < cap[curr][adj] && pot(curr, adj) + cost[curr][adj] < dist[adj]) {
        dist[adj] = pot(curr, adj) + cost[curr][adj];
        parent[adj] = -curr - 1;
        q.push(make_pair(-dist[adj], adj));
      }
    }
  }

  for(int i = 0; i < n; i++) { pi[i] += dist[i]; }
  return dist[dest];
}

pair<int, int> mcmf(int src, int sink) {
  memset(flow, false, sizeof(flow));
  memset(pi, 0, sizeof(pi));

  int minCost = 0, maxFlow = 0;
  while(dijkstra(src, sink) < INF) {
    int bot = INF;

    for(int v = sink, u = parent[v]; v != src; u = parent[v = u])
      bot = min(bot, flow[v][u] ? flow[v][u] : cap[u][v] - flow[u][v]);

    for(int v = sink, u = parent[v]; v != src; u = parent[v = u]) {
      if(flow[v][u]) { flow[v][u] = false; minCost -= cost[v][u]; }
      else { flow[u][v] = true; minCost += cost[u][v]; }
    }
    maxFlow += bot;
  }
  return make_pair(minCost, maxFlow);
}

// -----------------------------------------------

int main() {
  return 0;
}
