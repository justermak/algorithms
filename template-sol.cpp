#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#if LOCAL
#define dbg(o) ({ cout << #o << " = " << (o) << "\n"; o; })
#else
#define dbg(o) (o)
#endif

#define ff first
#define ss second
#define len(a) (int)a.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll l, ll r) { return uniform_int_distribution<ll> (l, r) (rnd); }

void vendory() {

}

void sol() {

}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#if LOCAL
    freopen("input.txt", "r", stdin);
    vendory();
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cout << "\n================================ " << i << " ================================" << endl;
        sol();
    }
#else
    vendory();
    sol();
#endif
    return (0-0);  // <3
}