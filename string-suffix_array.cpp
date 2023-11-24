void sol() {
    int n, ln;
    string s;
    cin >> n >> s;
    s += '#';
    n++;
    ln = (32 - __builtin_clz(n - 1));
    vector<int> p(n), p1(n), c(n), c1(n), cnt;
    iota(all(p), 0);
    sort(all(p), [&](int i, int j) { return s[i] < s[j]; });
    for (int i = 1; i < n; ++i) if (s[p[i]] != s[p[i - 1]]) c[p[i]] = i; else c[p[i]] = c[p[i - 1]];
    for (int k = 0; k < ln; ++k) {
        for (int i = 0; i < n; ++i) p1[i] = (p[i] - (1 << k) + n) % n;
        cnt.assign(n, 0);
        for (int i = 0; i < n; ++i) cnt[c[i]]++;
        for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) p[--cnt[c[p1[i]]]] = p1[i];
        c1[p[0]] = 0;
        for (int i = 1; i < n; ++i)
            if (c[p[i]] != c[p[i - 1]] || c[(p[i] + (1 << k)) % n] != c[(p[i - 1] + (1 << k) % n)]) c1[p[i]] = i;
            else c1[p[i]] = c1[p[i - 1]];
        c = c1;
    }
    vector<int> q(n), lcp(n);
    for (int i = 0; i < n; ++i) q[p[i]] = i;
    for (int i = 0, k = 0; i < n; ++i, k = max(0, k - 1)) {
        if (q[i] == n - 1) {
            k = 0;
            continue;
        }
        while (max(p[q[i]], p[q[i] + 1]) < n - k && s[p[q[i]] + k] == s[p[q[i] + 1] + k]) k++;
        lcp[q[i]] = k;
    }
}
