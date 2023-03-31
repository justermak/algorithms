const int MOD = 998244353, ROOT = 3;

ll pm(ll x, ll y) {
  ll res = 1;
  for (; y; y >>= 1) {
    if (y & 1) res = res * x % MOD;
    x = x * x % MOD;
  }
  return res;
}

vector<ll> fft(vector<ll> a, int inv = 0) {
  if (len(a) == 1) return a;
  int n = len(a), k = 32 - __builtin_clz(n - 1), t = 0;
  vector<int> rev(n);
  for (int i = 1; i < n; ++i) {
    if (i == (1 << t)) t++;
    rev[i] = rev[i - (1 << (t - 1))] + (1 << (k - t));
  }
  for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
  ll root = pm(ROOT, (MOD - 1) / n);
  if (inv) root = pm(root, MOD - 2);
  vector<ll> roots {1};
  for (int i = 1; i < n; ++i) roots.push_back(roots.back() * root % MOD);
  for (int l = 2; l <= n; l <<= 1) {
    for (int i = 0; i < n; i += l) {
      for (int j = 0; j < l / 2; ++j) {
        ll u = a[i + j], v = a[i + j + l / 2] * roots[n / l * j] % MOD;
        a[i + j] = (u + v) % MOD;
        a[i + j + l / 2] = (u - v + MOD) % MOD;
      }
    }
  }
  if (inv) {
    ll invn = pm(n, MOD - 2);
    for (int i = 0; i < n; ++i) a[i] = a[i] * invn % MOD;
  }
  return a;
}

vector<ll> operator*(vector<ll> a, vector<ll> b) {
  int n = 1 << (33 - __builtin_clz(max(len(a), len(b)) - 1));
  a.resize(n);
  b.resize(n);
  a = fft(a);
  b = fft(b);
  for (int i = 0; i < n; ++i) a[i] = a[i] * b[i] % MOD;
  return fft(a, 1);
}
