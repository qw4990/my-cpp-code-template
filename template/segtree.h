#include "defines.h"

class segtree {
public:
    struct node {
    };

    inline void init(int x, int pos) {
    }

    inline void apply(int x, int l, int r, int v) {
    }

    inline void push(int x, int l, int r) {
    }
    
    inline void pull_node(node &x, const node &lson, const node &rson) {
    }

    inline void pull(int x) {
        pull_node(tree[x], tree[lson(x)], tree[rson(x)]);
    }

    inline int lson(int x) {return x * 2;}
    inline int rson(int x) {return x * 2 + 1;}

    int n;
    VEC<node> tree;

    void build(int x, int l, int r) {
        if (l == r) {
            init(x, l);
            return;
        }
        int mid = (l+r) >> 1;
        build(lson(x), l, mid);
        build(rson(x), mid+1, r);
        pull(x);
    }

    template <typename M>
    void build(int x, int l, int r, const VEC<M> &vs) {
        if (l == r) {
            init(x, l);
            apply(x, l, r, vs[l]);
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
            pull_node(res, get(lson(x), l, mid, ll, mid), get(rson(x), mid+1, r, mid+1, rr));
        }
        pull(x);
        return res;
    }

    template <typename... M>
    void modify(int x, int l, int r, int ll, int rr, const M&... v) {
        if (l == ll && r == rr) {
            apply(x, l, r, v...);
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
        build(1, 1, n);
    }

    template <typename M>
    segtree(const vector<M> &v) {
        n = v.size(); // index starts from 1
        n--;
        assert(n >= 1);
        tree.resize(4 * n - 1);
        build(1, 1, n, v);
    }

    node get(int ll, int rr) {
        assert(0 < ll && ll <= rr && rr <= n);
        return get(1, 1, n, ll, rr);
    }

    node get(int p) {
        assert(0 < p && p <= n);
        return get(1, 1, n, p, p);
    }

    template <typename... M>
    void modify(int ll, int rr, const M&... v) {
        assert(0 < ll && ll <= rr && rr <= n);
        modify(1, 1, n, ll, rr, v...);
    }
};