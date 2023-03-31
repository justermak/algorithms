const int MAXN = 1 << 18;

vector<int> g[MAXN];
int p[MAXN], h[MAXN], sz[MAXN], go[MAXN], in[MAXN], out[MAXN];
ll a[2 * MAXN], b[MAXN];
int timer = 0;

void dfs_hsz(int u) {
  sz[u] = 1;
  for (auto &v : g[u]) {
    if (v != p[u]) {
      p[v] = u;
      h[v] = h[u] + 1;
      dfs_hsz(v);
      sz[u] += sz[v];
      if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
  }
}

void dfs_hld(int u) {
  in[u] = timer++;
  for (auto v : g[u]) if (v != p[u]) {
    go[v] = (v == g[u][0] ? go[u] : v);
    dfs_hld(v);
  }
  out[u] = timer;
}

void st_upd(int pos) {
  if (pos == 0) return;
  a[pos] = max(a[2 * pos], a[2 * pos + 1]);
  st_upd(pos / 2);
}

ll st_get(int l, int r, int pos = 1, int tl = 0, int tr = MAXN) {
  if (l <= tl && r >= tr) return a[pos];
  int tm = (tl + tr) / 2;
  ll res = -INFll;
  if (l < tm) res = max(res, st_get(l, r, 2 * pos, tl, tm));
  if (r > tm) res = max(res, st_get(l, r, 2 * pos + 1, tm, tr));
  return res;
}

void add(int u, ll w) {
  a[in[u] + MAXN] += w;
  st_upd((in[u] + MAXN) / 2);
}

ll get_path(int u, int v) {
  ll res = -INFll;
  for (;go[u] != go[v];) {
    if (h[go[u]] > h[go[v]]) swap(u, v);
    res = max(res, st_get(in[go[v]], in[v] + 1));
    v = p[go[v]];
  }
  if (in[u] > in[v]) swap(u, v);
  return max(res, st_get(in[u], in[v] + 1));
}

ll get_tree(int u) {
  return st_get(in[u], out[u]);
}

void sol() {
  //process input, run dfs-es, init st
}
