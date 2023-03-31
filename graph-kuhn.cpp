vector<int> used, l, r;
vector<vector<int>> g;

bool dfs(int u) {
  used[u] = 1;
  for (auto v : g[u]) {
    if (r[v] == -1 || (!used[r[v]] && dfs(r[v]))) {
      r[v] = u;
      l[u] = v;
      return 1;
    }
  }
  return 0;
}

void sol() {
  l.assign(n, -1);
  r.assign(m, -1);
  for (int t = 1; t;) {
    t = 0;
    used.assign(n, 0);
    for (int i = 0; i < n; ++i) if (l[i] == -1 && dfs(i)) t = 1;
  }
}
