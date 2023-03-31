const int MAXN = 1e6, alph = 26;

string s;
int n, sz = 1, last = 0, suf[2 * MAXN], ls[2 * MAXN], go[2 * MAXN][alph];

void sol() {
  cin >> n >> s;
  for (int i = 0; i < 2 * MAXN; ++i) fill(go[i], go[i] + alph, -1);
  suf[0] = -1;
  for (char cc : s) {
    int c = cc - 'a', cur = sz++;
    ls[cur] = ls[last] + 1;
    int p = last;
    for (; p != -1; p = suf[p]) {
      if (go[p][c] == -1) {
        go[p][c] = cur;
      } else {
        int q = go[p][c];
        if (ls[q] == ls[p] + 1) {
          suf[cur] = q;
          break;
        } else {
          int cpy = sz++;
          copy(go[q], go[q] + alph, go[cpy]);
          ls[cpy] = ls[p] + 1;
          suf[cur] = cpy;
          suf[cpy] = suf[q];
          suf[q] = cpy;
          for (; p != -1; p = suf[p]) {
            go[p][c] = cpy;
          }
          break;
        }
      }
    }
    last = cur;
  }
}
