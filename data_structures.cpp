

// class segtree {
//  public:
//   struct node {
//     int add = 0;
//     int mn = 0;
 
//     void apply(int l, int r, int v) {
//       mn += v;
//       add += v;
//     }
//   };
 
//   node unite(const node &a, const node &b) const {
//     node res;
//     res.mn = min(a.mn, b.mn);
//     return res;
//   }
 
//   inline void push(int x, int l, int r) {
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     if (tree[x].add != 0) {
//       tree[x + 1].apply(l, y, tree[x].add);
//       tree[z].apply(y + 1, r, tree[x].add);
//       tree[x].add = 0;
//     }
//   }
 
//   inline void pull(int x, int z) {
//     tree[x] = unite(tree[x + 1], tree[z]);
//   }
 
//   int n;
//   vector<node> tree;
 
//   void build(int x, int l, int r) {
//     if (l == r) {
//       return;
//     }
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     build(x + 1, l, y);
//     build(z, y + 1, r);
//     pull(x, z);
//   }
 
//   template <typename M>
//   void build(int x, int l, int r, const vector<M> &v) {
//     if (l == r) {
//       tree[x].apply(l, r, v[l]);
//       return;
//     }
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     build(x + 1, l, y, v);
//     build(z, y + 1, r, v);
//     pull(x, z);
//   }
 
//   node get(int x, int l, int r, int ll, int rr) {
//     if (ll <= l && r <= rr) {
//       return tree[x];
//     }
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     push(x, l, r);
//     node res{};
//     if (rr <= y) {
//       res = get(x + 1, l, y, ll, rr);
//     } else {
//       if (ll > y) {
//         res = get(z, y + 1, r, ll, rr);
//       } else {
//         res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
//       }
//     }
//     pull(x, z);
//     return res;
//   }
 
//   template <typename... M>
//   void modify(int x, int l, int r, int ll, int rr, const M&... v) {
//     if (ll <= l && r <= rr) {
//       tree[x].apply(l, r, v...);
//       return;
//     }
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     push(x, l, r);
//     if (ll <= y) {
//       modify(x + 1, l, y, ll, rr, v...);
//     }
//     if (rr > y) {
//       modify(z, y + 1, r, ll, rr, v...);
//     }
//     pull(x, z);
//   }
 
//   int find_first_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
//     if (l == r) {
//       return l;
//     }
//     push(x, l, r);
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     int res;
//     if (f(tree[x + 1])) {
//       res = find_first_knowingly(x + 1, l, y, f);
//     } else {
//       res = find_first_knowingly(z, y + 1, r, f);
//     }
//     pull(x, z);
//     return res;
//   }
 
//   int find_first(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
//     if (ll <= l && r <= rr) {
//       if (!f(tree[x])) {
//         return -1;
//       }
//       return find_first_knowingly(x, l, r, f);
//     }
//     push(x, l, r);
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     int res = -1;
//     if (ll <= y) {
//       res = find_first(x + 1, l, y, ll, rr, f);
//     }
//     if (rr > y && res == -1) {
//       res = find_first(z, y + 1, r, ll, rr, f);
//     }
//     pull(x, z);
//     return res;
//   }
 
//   int find_last_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
//     if (l == r) {
//       return l;
//     }
//     push(x, l, r);
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     int res;
//     if (f(tree[z])) {
//       res = find_last_knowingly(z, y + 1, r, f);
//     } else {
//       res = find_last_knowingly(x + 1, l, y, f);
//     }
//     pull(x, z);
//     return res;
//   }
 
//   int find_last(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
//     if (ll <= l && r <= rr) {
//       if (!f(tree[x])) {
//         return -1;
//       }
//       return find_last_knowingly(x, l, r, f);
//     }
//     push(x, l, r);
//     int y = (l + r) >> 1;
//     int z = x + ((y - l + 1) << 1);
//     int res = -1;
//     if (rr > y) {
//       res = find_last(z, y + 1, r, ll, rr, f);
//     }
//     if (ll <= y && res == -1) {
//       res = find_last(x + 1, l, y, ll, rr, f);
//     }
//     pull(x, z);
//     return res;
//   }
 
//   segtree(int _n) : n(_n) {
//     assert(n > 0);
//     tree.resize(2 * n - 1);
//     build(0, 0, n - 1);
//   }
 
//   template <typename M>
//   segtree(const vector<M> &v) {
//     n = v.size();
//     assert(n > 0);
//     tree.resize(2 * n - 1);
//     build(0, 0, n - 1, v);
//   }
 
//   node get(int ll, int rr) {
//     assert(0 <= ll && ll <= rr && rr <= n - 1);
//     return get(0, 0, n - 1, ll, rr);
//   }
 
//   node get(int p) {
//     assert(0 <= p && p <= n - 1);
//     return get(0, 0, n - 1, p, p);
//   }
 
//   template <typename... M>
//   void modify(int ll, int rr, const M&... v) {
//     assert(0 <= ll && ll <= rr && rr <= n - 1);
//     modify(0, 0, n - 1, ll, rr, v...);
//   }
 
//   // find_first and find_last call all FALSE elements
//   // to the left (right) of the sought position exactly once
 
//   int find_first(int ll, int rr, const function<bool(const node&)> &f) {
//     assert(0 <= ll && ll <= rr && rr <= n - 1);
//     return find_first(0, 0, n - 1, ll, rr, f);
//   }
 
//   int find_last(int ll, int rr, const function<bool(const node&)> &f) {
//     assert(0 <= ll && ll <= rr && rr <= n - 1);
//     return find_last(0, 0, n - 1, ll, rr, f);
//   }
// };



// struct SegTreeNode {
// 	int l, r;
// 	pii val;
// 	int toAdd;
 
// 	SegTreeNode() : l(-1), r(-1), val(), toAdd(0) {}
// 	SegTreeNode(int _l, int _r) : l(_l), r(_r), val(mp(0, _l)), toAdd(0) {}
 
// 	void apply(int x) {
// 		val.first += x;
// 		toAdd += x;
// 	}
// };
// struct SegmentTree {
// 	vector<SegTreeNode> tree;
// 	int L;
 
// 	SegmentTree() : tree(), L(-1) {}
// 	SegmentTree(int _L) {
// 		L = _L;
// 		while(L & (L - 1)) L++;
// 		tree.resize(2 * L);
// 		for (int i = 0; i < L; i++)
// 			tree[L + i] = SegTreeNode(i, i + 1);
// 		for (int i = L - 1; i > 0; i--)
// 			tree[i] = SegTreeNode(tree[2 * i].l, tree[2 * i + 1].r);
// 	}
 
// 	void push(int v) {
// 		for (int u = 2 * v; u < 2 * v + 2; u++) {
// 			tree[u].apply(tree[v].toAdd);
// 		}
// 		tree[v].toAdd = 0;
// 	}
// 	void update(int v) {
// 		tree[v].val = min(tree[2 * v].val, tree[2 * v + 1].val);
// 	}
 
// 	void addOnSegm(int v, int l, int r, int x) {
// 		if (l <= tree[v].l && tree[v].r <= r) {
// 			tree[v].apply(x);
// 			return;
// 		}
// 		if (l >= tree[v].r || tree[v].l >= r) return;
// 		push(v);
// 		for (int u = 2 * v; u < 2 * v + 2; u++)
// 			addOnSegm(u, l, r, x);
// 		update(v);
// 	}
// 	pii getMin(int v, int l, int r) {
// 		if (l <= tree[v].l && tree[v].r <= r) return tree[v].val;
// 		if (l >= tree[v].r || tree[v].l >= r) return mp((int)1e9, -1);
// 		push(v);
// 		return min(getMin(2 * v, l, r), getMin(2 * v + 1, l, r));
// 	}
// };












// struct SegmentTree {
//     int n;
//     std::vector<int> sum, max;
//     void init(int _n) {
//         n = _n;
//         sum.assign(4 * n, 0);
//         max.assign(4 * n, 0);
//     }
//     void pull(int p) {
//         sum[p] = sum[2 * p] + sum[2 * p + 1];
//         max[p] = std::max(max[2 * p + 1], max[2 * p] + sum[2 * p + 1]);
//     }
//     void modify(int p, int l, int r, int pos, int v) {
//         if (r - l == 1) {
//             sum[p] = v;
//             max[p] = std::max(0, v);
//             return;
//         }
//         int m = (l + r) / 2;
//         if (pos < m) {
//             modify(2 * p, l, m, pos, v);
//         } else {
//             modify(2 * p + 1, m, r, pos, v);
//         }
//         pull(p);
//     }
//     void modify(int pos, int v) {
//         modify(1, 0, n, pos, v);
//     }
// };