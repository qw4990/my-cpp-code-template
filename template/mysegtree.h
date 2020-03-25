#include "defines.h"

class segtree {
public:
    struct node {
        int add = 0;
        int mn = 0;

        void apply(int l, int r, int v) {
            mn += v;
            add += v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        res.mn = min(a.mn, b.mn);
        return res;
    }

    inline void push(int x, int l, int r) {
        if (tree[x].add != 0) {
            int mid = (l + r) >> 1;
            tree[lson(x)].apply(l, mid, tree[x].add);
            tree[rson(x)].apply(mid+1, r, tree[x].add);
            tree[x].add = 0;
        }
    }

    inline void pull(int x) {
        tree[x] = unite(tree[x*2], tree[x*2+1]);
    }

    inline int lson(int x) {return x * 2;}
    inline int rson(int x) {return x * 2 + 1;}

    int n;
    VEC<node> tree;

    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int mid = (l+r) >> 1;
        build(lson(x), l, mid);
        build(rson(x), mid+1, r);
        pull(x);
    }

    void build(int x, int l, int r, const VEC<int> &vs) {
        if (l == r) {
            tree[x].apply(l, r, vs[l]);
            return;
        }
        int mid = (l+r) >> 1;
        build(lson(x), l, mid, vs);
        build(rson(x), mid+1, r, vs);
        pull(x);
    }

    node get(int x, int l, int r, int ll, int rr) {
        if (l == ll && r == rr) {
            return tree[x];
        }
        push(x, l, r);
        int mid = (l+r) >> 1;
        node res{};
        if (rr <= mid) {
            res = get(lson(x), l, mid, ll, rr);
        } else if (ll > mid) {
            res = get(rson(x), mid+1, r, ll, rr);
        } else {
            res = unite(get(lson(x), l, mid, ll, mid), get(rson(x), mid+1, r, mid+1, rr));
        }
        pull(x);
        return res;
    }

    template <typename... M>
    void modify(int x, int l, int r, int ll, int rr, const M&... v) {
        if (l == ll && r == rr) {
            tree[x].apply(l, r, v...);
            return;
        }
        push(x, l, r);
        int mid = (l + r) >> 1;
        if (rr <= mid) {
            modify(lson(x), l, mid, ll, rr, v...);
        } else if (ll > mid) {
            modify(rson(x), mid+1, r, ll, rr, v...);
        } else {
            modify(lson(x), l, mid, ll, mid, v...);
            modify(rson(x), mid+1, r, mid+1, rr, v...);
        }
        pull(x);
    }

    segtree(int _n) : n(_n) {
        tree.resize(4 * n - 1);
        build(0, 0, n - 1);
    }

    template <typename M>
    segtree(const vector<M> &v) {
        n = v.size();
        assert(n > 0);
        tree.resize(4 * n - 1);
        build(0, 0, n - 1, v);
    }

    node get(int ll, int rr) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return get(0, 0, n - 1, ll, rr);
    }

    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(0, 0, n - 1, p, p);
    }

    template <typename... M>
    void modify(int ll, int rr, const M&... v) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        modify(0, 0, n - 1, ll, rr, v...);
    }
};
