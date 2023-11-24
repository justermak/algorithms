struct node {
    int sz = 1, v = 0;
    ll s = 0;
    node *l = 0, *r = 0;

    node() {}

    node(int v, node *l, node *r) : v(v), l(l), r(r) {
        s = v + (l == 0 ? 0 : l->s) + (r == 0 ? 0 : r->s);
        sz = 1 + (l == 0 ? 0 : l->sz) + (r == 0 ? 0 : r->sz);
    }

    node(node *n) {
        if (n == 0) return;
        v = n->v;
        sz = n->sz;
        s = n->s;
        l = n->l;
        r = n->r;
    }
};

int getsz(node *n) {
    return (n == 0 ? 0 : n->sz);
}

ll gets(node *n) {
    return (n == 0 ? 0 : n->s);
}

void upd(node *n) {
    if (n == 0) return;
    n->sz = 1 + getsz(n->l) + getsz(n->r);
    n->s = n->v + gets(n->l) + gets(n->r);
}

node *merge(node *l, node *r) {
    if (l == 0) return new node(r);
    if (r == 0) return new node(l);
    if (getsz(l) > rng(0, getsz(l) + getsz(r)))
        return new node(l->v, l->l, merge(l->r, r));
    return new node(r->v, merge(l, r->l), r->r);
}

void split(node *nn, node *&l, node *&r, int x) {
    if (nn == 0) {
        l = r = 0;
        return;
    }
    node *n = new node(nn);
    if (x <= getsz(n->l)) {
        split(n->l, l, n->l, x);
        r = n;
        upd(r);
    } else {
        split(n->r, n->r, r, x - getsz(n->l) - 1);
        l = n;
        upd(l);
    }
}

int n, m;
vector<node *> h;

node *insert(int i, int p, int x) {
    node *n = new node(x, 0, 0);
    node *l, *r;
    split(h[i], l, r, p);
    return merge(merge(l, n), r);
}

ll sum(node *n, int l, int r) {
    ll res = 0;
    if (n == 0) return 0;
    if (l == 0 && r == getsz(n) - 1) return gets(n);
    if (l < getsz(n->l)) res += sum(n->l, l, min(getsz(n->l) - 1, r));
    if (r > getsz(n->l)) res += sum(n->r, max(0, l - getsz(n->l) - 1), r - getsz(n->l) - 1);
    if (l <= getsz(n->l) && r >= getsz(n->l)) res += n->v;
    return res;
}
