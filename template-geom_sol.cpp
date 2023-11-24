const ld EPS = 1e-9;

struct point {
    ld x = 0, y = 0;

    point() {}

    point(ld x, ld y) : x(x), y(y) {}

    bool operator<(const point &p) const {
        return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
    }

    bool operator>(const point &p) const {
        return x > p.x + EPS || (abs(x - p.x) < EPS && y > p.y + EPS);
    }

    bool operator==(const point &p) const {
        return abs(x - p.x) < EPS && abs(y - p.y) < EPS;
    }

    point operator+(const point &p) const {
        return point(x + p.x, y + p.y);
    }

    point operator-(const point &p) const {
        return point(x - p.x, y - p.y);
    }

    point operator*(const ld &k) const {
        return point(x * k, y * k);
    }

    point operator/(const ld &k) const {
        return point(x / k, y / k);
    }

    ld operator*(const point &p) const {
        return x * p.x + y * p.y;
    }

    ld operator%(const point &p) const {
        return x * p.y - y * p.x;
    }

    point left() const {
        return point(-y, x);
    }

    ld lengthsqr() const {
        return x * x + y * y;
    }

    ld length() const {
        return sqrt(this->lengthsqr());
    }

    ld dist(const point &p) const {
        return (*this - p).length();
    }
};

ostream &operator<<(ostream &out, const point &p) {
    return out << p.x << ' ' << p.y;
}

istream &operator>>(istream &in, point &p) {
    return in >> p.x >> p.y;
}

struct matrix {
    vector <vector<ld>> m = {{1, 0},
                             {0, 1}};

    matrix() {}

    matrix(vector <vector<ld>> m) : m(std::move(m)) {}

    matrix(ld phi) : m({{cos(phi), -sin(phi)},
                        {sin(phi), cos(phi)}}) {}

    matrix operator*(const matrix &b) const {
        matrix c;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    c.m[i][j] += m[i][k] * b.m[k][j];
                }
            }
        }
        return c;
    }

    point operator*(const point &p) const {
        return point(m[0][0] * p.x + m[0][1] * p.y, m[1][0] * p.x + m[1][1] * p.y);
    }
};

struct line {
    point p = point(), d = point();

    line() {}

    line(point p, point d) : p(p), d(d) {}

    line(ld a, ld b, ld c) : p(point(-a * c / (a * a + b * b), -b * c / (a * a + b * b))), d(point(-b, a)) {}

    ld dist(point a) const {
        return d % (a - p) / d.length();
    }

    bool parallel(const line &l) const {
        return abs(d % l.d) < EPS;
    }

    ld t(const line &l) const {
        return (l.p - p) % l.d / (d % l.d);
    }

    ld lt(const line &l) const {
        return (p - l.p) % d / (l.d % d);
    }

    point operator()(ld t) const {
        return p + d * t;
    }

    bool intersects(const line &l) const { // segment intersection
        return !parallel(l) && -EPS < lt(l) && lt(l) < 1 + EPS;
    }

    point intersect(const line &l) const {
        return p + d * t(l);
    }
};

ostream &operator<<(ostream &out, const line &l) {
    return out << l.p << " + " << l.d << "t";
}

istream &operator>>(istream &in, line &l) {
    return in >> l.p >> l.d;
}

struct polygon {
    vector <point> p;

    polygon() {}

    polygon(vector <point> p) : p(p) {}

    polygon convex_hull() {
        vector <point> h;
        sort(all(p));
        for (int i = 0; i < len(p); ++i) {
            while (len(h) >= 2 && (h[len(h) - 1] - h[len(h) - 2]) % (p[i] - h[len(h) - 2]) < EPS) {
                h.pop_back();
            }
            h.push_back(p[i]);
        }
        for (int i = len(p) - 2, t = len(h) + 1; i >= 0; --i) {
            while (len(h) >= t && (h[len(h) - 1] - h[len(h) - 2]) % (p[i] - h[len(h) - 2]) < EPS) {
                h.pop_back();
            }
            h.push_back(p[i]);
        }
        h.pop_back();
        return polygon(h);
    }

    ld area() const {
        ld s = 0;
        for (int i = 0; i < len(p); ++i) {
            s += p[i] % p[(i + 1) % len(p)];
        }
        return s / 2;
    }

    vector <line> sides() {
        vector <line> s;
        for (int i = 0; i < len(p); ++i) {
            s.push_back(line(p[i], p[(i + 1) % len(p)] - p[i]));
        }
        return s;
    }

    bool in(point p) {
        vector <line> s = sides();
        line nice = line(p, point(69, 420));
        int cnt = 0;
        for (int i = 0; i < len(s); ++i) {
            cnt += nice.intersects(s[i]) && nice.t(s[i]) > -EPS;
        }
        return cnt & 1;
    }

    bool onBorder(point p) {
        vector <line> s = sides();
        for (int i = 0; i < len(s); ++i) {
            line a(p, s[i].d.left());
            if (a.d.length() > EPS && abs(s[i].dist(p)) < EPS && a.intersects(s[i])) {
                return true;
            } else if (p == s[i].p) {
                return true;
            }
        }
        return false;
    }
};

struct circle {
    point o = point();
    ld r = 0;

    circle() {}

    circle(point o, ld r) : o(o), r(r) {}

    line diff(circle c) const {
        return line(2 * (c.o.x - o.x), 2 * (c.o.y - o.y), o.lengthsqr() - c.o.lengthsqr() - r * r + c.r * c.r);
    }

    vector <point> intersect(line l) const {
        vector <point> ans;
        ld t = l.dist(o);
        if (t > r + EPS) {
            return ans;
        }
        line n = line(o, l.d.left());
        if (abs(t - r) < EPS) {
            ans.push_back(l.intersect(n));
            return ans;
        }
        ld d = sqrt(r * r - t * t);
        ans.push_back(l.intersect(n) + l.d / l.d.length() * d);
        ans.push_back(l.intersect(n) - l.d / l.d.length() * d);
        sort(all(ans));
        return ans;
    }
};

ostream &operator<<(ostream &out, const circle &c) {
    return out << c.o << " - " << c.r;
}

istream &operator>>(istream &in, circle &c) {
    return in >> c.o >> c.r;
}