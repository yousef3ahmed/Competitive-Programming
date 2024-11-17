struct DSU {
  vector<int> par, sz;
  set<int> roots;

  void init(int n) {
    par.assign(n + 1, {});
    iota(par.begin(), par.end(), 0);
    roots = set<int>(par.begin(), par.end());
    sz.assign(n + 1, 1);
  }

  int find(int u) {
    while (u ^ par[u]) {
      u = par[u];
    }
    return u;
  }

  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) {
      return false;
    }
    if (sz[u] < sz[v]) {
      swap(u, v);
    }
    sz[u] += sz[v];
    roots.erase(v);
    par[v] = u;
    return true;
  }

  int size(int u) {
    return sz[find(u)];
  }

};
