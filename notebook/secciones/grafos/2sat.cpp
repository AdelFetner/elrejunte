// Usage:
// 1. Create with n = number of variables (0-indexed)
// 2. Add restrictions through the existing methods, using ~X for
//    negating variable X for example.
// 3. Call satisf() to check whether there is a solution or not.
// 4. Find a valid assigment by looking at verdad[cmp[2*X]] for each
//    variable X
struct Sat2 {
  // We have a vertex representing a variable and other for its
  // negation. Every edge stored in G represents an implication.
  vector<vector<int>> G;
  // idx[i]=index assigned in the dfs
  // lw[i]=lowest index(closer from the root) reachable from i
  // verdad[cmp[2*i]]=valor de la variable i
  int N, qidx, qcmp;
  vector<int> lw, idx, cmp, verdad;
  stack<int> q;
  Sat2(int n) : G(2 * n), N(n) {}
  void tjn(int v) {
    lw[v] = idx[v] = ++qidx;
    q.push(v), cmp[v] = -2;
    forall(it, G[v]) if (!idx[*it] || cmp[*it] == -2) {
      if (!idx[*it]) tjn(*it);
      lw[v] = min(lw[v], lw[*it]);
    }
    if (lw[v] == idx[v]) {
      int x;
      do { x = q.top(), q.pop(), cmp[x] = qcmp; } while (x != v);
      verdad[qcmp] = (cmp[v ^ 1] < 0);
      qcmp++;
    }
  }
  bool satisf() {  // O(N)
    idx = lw = verdad = vector<int>(2 * N, 0);
    cmp = vector<int>(2 * N, -1);
    qidx = qcmp = 0;
    forn(i, N) {
      if (!idx[2 * i]) tjn(2 * i);
      if (!idx[2 * i + 1]) tjn(2 * i + 1);
    }
    forn(i, N) if (cmp[2 * i] == cmp[2 * i + 1]) return false;
    return true;
  }
  // a -> b, here ids are transformed to avoid negative numbers
  void addimpl(int a, int b) {
    a = a >= 0 ? 2 * a : 2 * (~a) + 1;
    b = b >= 0 ? 2 * b : 2 * (~b) + 1;
    G[a].pb(b), G[b ^ 1].pb(a ^ 1);
  }
  void addor(int a, int b) { addimpl(~a, b); }  // a | b = ~a -> b
  void addeq(int a, int b) {                    // a = b, a <-> b (iff)
    addimpl(a, b);
    addimpl(b, a);
  }
  void addxor(int a, int b) { addeq(a, ~b); }  // a xor b
  void force(int x, bool val) {                // force x to take val
    if (val) addimpl(~x, x);
    else addimpl(x, ~x);
  }
  // At most 1 true in all v
  void atmost1(vector<int> v) {
    int auxid = N;
    N += sz(v);
    G.rsz(2 * N);
    forn(i, sz(v)) {
      addimpl(auxid, ~v[i]);
      if (i) {
        addimpl(auxid, auxid - 1);
        addimpl(v[i], auxid - 1);
      }
      auxid++;
    }
    assert(auxid == N);
  }
};
