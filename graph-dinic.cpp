struct edge {
  int u = -1, v = -1, c = 0, f = 0;
  edge() {}
  edge(int u, int v, int c): u(u), v(v), c(c) {}
};

int n, m, s, t, b;
vector<int> q, d, h;
vector<edge> e;
vector<vector<int>> g;

int bfs() {
  d.assign(n, -1);
  d[s] = 0;
  int l = 0, r = 0;
  q[r++] = s;
  for (; r - l > 0;) {
    int u = q[l++];
    for (auto i : g[u]) if (d[e[i].v] == -1 && (e[i].c - e[i].f) >= b) {
      q[r++] = e[i].v;
      d[e[i].v] = d[u] + 1;
    }
  }
  return (d[t] != -1);
}

int dfs(int u, int f) {
  if (u == t) return f;
  if (f == 0) return 0;
  for (; h[u] < len(g[u]); ++h[u]) {
    int j = g[u][h[u]];
    if (d[e[j].v] == d[u] + 1 && e[j].c - e[j].f >= b) {
      int fl = dfs(e[j].v, min(f, e[j].c - e[j].f));
      if (fl > 0) {
        e[j].f += fl;
        e[j ^ 1].f -= fl;
        return fl;
      }
    }
  }
  return 0;
}

void sol() {
  cin >> n >> m >> s >> t;
  s--; t--;
  e.resize(2 * m);
  g.resize(n);
  q.resize(n);
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    u--; v--;
    e[2 * i] = edge(u, v, c);
    e[2 * i + 1] = edge(v, u, 0);
    g[u].push_back(2 * i);
    g[v].push_back(2 * i + 1);
  }
  int fl = 0;
  for (b = (1 << 30); b > 0; b >>= 1) {
    for (; bfs();) {
      h.assign(n, 0);
      for (int f = dfs(s, INF); f > 0; f = dfs(s, INF)) fl += f;
    }
  }
  cout << fl << endl;
}
