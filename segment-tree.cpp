/**
 * Segment Tree with lazy propagation
 *
 * Data structure that allows doing aggregated range queries and updates, given
 * that the data about an interval can be built by joining sub-intervals.
 *
 * Parameters:
 *   - `Node` (type): a class able to hold all the relevant information about
 *                    an interval. Must implement:
 *       * A default constructor;
 *       * A constructor receiving the index of a single-element interval and
 *         its initial value;
 *       * A member `Node join(Node& node)`, returning a new `Node` with the
 *         merged data from this node and the argument.
 *   - `Op` (type): a class representing an update operation on the tree (can be
 *                  dummy if updates are not needed). Must implement:
 *       * A default constructor;
 *       * A member `void apply(Node& node, int st, int end)`, applying the
 *         operation to `node` (which contains information from the range
 *         [`st`, `end`]);
 *       * A member `Op merge(Op& op, int st, int end)`, returning a new `Op`
 *         representing the application of this operation followed by the
 *         argument (to be applied later in the range [`st`, `end`]);
 *   - `n`: the number of elements to store.
 *
 * Operations:
 *   - `build(int* arr)` seeds the tree with initial data;
 *   - `query(int i, int j)` returns a `Node` containing aggregated information
 *     for the range [`i`, `j`];
 *   - `update(int i, int j, Op op)` applies the operation `Op` to the range
 *     [`i`, `j`].
 *
 * Complexity:
 *   - Space: O(n*log(n));
 *   - Time:
 *       * `init`: O(n*log(n));
 *       * `query`: O(log(n));
 *       * `update`: O(log(n)).
 */

#include <vector>

using namespace std;

template<class Node, class Op> struct SegTree {
  int size;
  vector<Node> tree;
  vector<bool> hasPending;
  vector<Op> pending;

  SegTree(int n) {
    size = n;
    tree.resize(4 * n + 1);
    hasPending.resize(4 * n + 1);
    pending.resize(4 * n + 1);
  }

  SegTree(int n, int* arr): SegTree(n) {
    build(arr);
  }

  inline int left(int node) { return 2 * node; }
  inline int right(int node) { return 2 * node + 1; }

  void build(int* arr, int node, int st, int end) {
    if (st == end) { tree[node] = Node(st, arr[st]); return; }

    build(arr, left(node), st, (st + end) / 2);
    build(arr, right(node), (st + end) / 2 + 1, end);
    tree[node] = tree[left(node)].join(tree[right(node)]);
  }

  void applyPending(int node, int st, int end) {
    if(hasPending[node]) {
      update(left(node), st, (st + end) / 2, st, end, pending[node]);
      update(right(node), (st + end) / 2 + 1, end, st, end, pending[node]);
      hasPending[node] = false;
    }
  }

  Node query(int node, int st, int end, int i, int j) {
    if (j < st || i > end) return Node();
    if (st >= i && end <= j) return tree[node];

    applyPending(node, st, end);
    Node p1 = query(left(node), st, (st + end) / 2, i, j);
    Node p2 = query(right(node), (st + end) / 2 + 1, end, i, j);
    return p1.join(p2);
  }

  void update(int node, int st, int end, int i, int j, Op op) {
    if (j < st || i > end) return;
    if (st == end) { op.apply(tree[node], st, end); return; }
    if (st >= i && end <= j) {
      op.apply(tree[node], st, end);
      pending[node] = hasPending[node] ? pending[node].merge(op, st, end) : op;
      hasPending[node] = true;
      return;
    }
    applyPending(node, st, end);
    if(i <= (st + end) / 2) update(left(node), st, (st + end) / 2, i, j, op);
    if(j > (st + end) / 2) update(right(node), (st + end) / 2 + 1, end, i, j, op);
    tree[node] = tree[left(node)].join(tree[right(node)]);
  }

  void build(int* arr) { build(arr, 1, 0, size - 1); }
  Node query(int i, int j) { return query(1, 0, size - 1, i, j); }
  void update(int i, int j, Op op) { return update(1, 0, size - 1, i, j, op); }
};

// -----------------------------------------------

#include <algorithm>
#include <iostream>

#define MAXN 10000
#define INF 1e9

struct Node {
  int minVal, maxVal;
  Node(): minVal(INF), maxVal(-INF) {}
  Node(int idx, int val): minVal(val), maxVal(val) {}

  Node join(Node& o) {
    Node n;
    n.minVal = min(minVal, o.minVal);
    n.maxVal = max(maxVal, o.maxVal);
    return n;
  }
};

struct Op {
  char code; int arg;

  Op() {} // nop
  Op(char _code, int _arg): code(_code), arg(_arg) {}

  void apply(Node& node, int st, int end) {
    switch(code) {
      case 's': // set values in range to `arg`
        node.minVal = node.maxVal = arg;
        break;
      case 'a': // add `n` to all values in range
        node.minVal += arg; node.maxVal += arg;
        break;
    }
  }

  Op merge(Op& op, int st, int end) {
    if(op.code == 's') return op;
    return Op(code, arg + op.arg);
  }
};

int arr[MAXN];

int main() {
  int n = 100;
  SegTree<Node, Op> tree(n, arr);

  char code; int st, end, arg;
  cout << "> ";
  while(cin >> code >> st >> end >> arg) {
    switch(code) {
      case 's':
      case 'a':
        tree.update(st, end, Op(code, arg));
        break;
      case 'm':
        cout << tree.query(st, end).minVal << endl;
        break;
      case 'M':
        cout << tree.query(st, end).maxVal << endl;
        break;
      default:
        cout << "Invalid command." << endl;
    }
    cout << "> ";
  }
}
