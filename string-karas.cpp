const int MAXN = 1e6, alph = 26;

int term[MAXN], lnk[MAXN], go[MAXN][alph], q[MAXN], sz = 1;

void add(string s) {
    int cur = 0;
    for (auto c: s) {
        if (!go[cur][c - 'a']) go[cur][c - 'a'] = sz++;
        cur = go[cur][c - 'a'];
    }
    term[cur] = cur;
}

void bfs() {
    int l = 0, r = 1;
    while (r - l > 0) {
        int u = q[l++], v = lnk[u];
        if (!term[u]) term[u] = term[v];
        for (int c = 0; c < alph; ++c) {
            if (go[u][c]) {
                lnk[go[u][c]] = (u ? go[v][c] : 0);
                q[r++] = go[u][c];
            } else {
                go[u][c] = go[v][c];
            }
        }
    }
}

void sol() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add(s);
    }
    bfs();
    int cur = 0;
    for (int i = 0; i < len(s); ++i) {
        cur = go[cur][s[i] - 'a'];
        for (int tmp = cur; tmp; tmp = term[lnk[tmp]]) {
            if (tmp == term[tmp]) cout << i << ' ' << d[id[tmp]] << endl;
        }
    }
}
