struct node {
  int sz = 1, v = 0;
  ll s = 0;
  node *l = 0, *r = 0;
  node() {}
  node(int v): v(v), s(v) {}
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

void merge(node *&n, node *l, node *r) {
  if (l == 0) { n = r; return; }
  if (r == 0) { n = l; return; }
  if (d(rng) < 1.0 * getsz(l) / (getsz(l) + getsz(r))) {
    merge(l->r, l->r, r);
    n = l;
    upd(n);
  } else {
    merge(r->l, l, r->l);
    n = r;
    upd(n);
  }
}

void split(node *n, node *&l, node *&r, int x) {
  if (n == 0) { l = r = 0; return; }
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

void insert(node *&h, int p, int x) {
  node *n = new node(x);
  node *l, *r;
  split(h, l, r, p);
  merge(l, l, n);
  merge(h, l, r);
}

ll sum(node* n, int l, int r) {
  ll res = 0;
  if (n == 0) return 0;
  if (l == 0 && r == getsz(n) - 1) return gets(n);
  if (l < getsz(n->l)) res += sum(n->l, l, min(getsz(n->l), r));
  if (r > getsz(n->l)) res += sum(n->r, max(0, l - getsz(n->l) - 1), r - getsz(n->l) - 1);
  if (l <= getsz(n->l) && r >= getsz(n->l)) res += n->v;
  return res;
}
