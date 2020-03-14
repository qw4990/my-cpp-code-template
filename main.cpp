#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <set>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 500005
#define LL long long
#define INT(n) int n;scanf("%d", &n);
#define FOR(i, n) for(int i = 0; i < n; i ++)
#define FOR_BE(i, b, e) for(int i = b; i < e; i++)
#define FOR_IT(begin, end) for(auto it = begin; it != end; it++)
#define COPY(dst, src, n) for(int i = 0; i < n; i++) {*dst=*src;dst++;src++;}
#define RESET(begin, end, v) for(auto it = begin; it != end; it++) *it=v;
#define VEC vector
#define INPUT_VEC(T, vs, n) vector<T> vs(n); for(int i = 0; i < n; i++) cin >> vs[i];
#define OUTPUT_VEC(vs) for(auto it=vs.begin(); it != vs.end(); it++) cout << *it << " "; cout << endl;
#define OUTPUT_BE(begin, end) for(auto it = begin; it != end; it++) cout << *it << " "; cout << endl;
#define PII pair<int, int>
#define FUNCTOR(name, ret, args, body) struct name {ret operator() args body};
#define PQ priority_queue

#define LS(k) (k*2)
#define RS(k) (k*2+1)
class SegmentTree {
public:
    LL *sum;
    int *L, *R, *rights, *flags;
    SegmentTree(int n) {
        sum = new LL[n*4];
        L = new int[n*4];
        R = new int[n*4];
        rights = new int[n*4];
        flags = new int[n*4];
    }
    
    ~SegmentTree() {
    }

    void Build(int k, int l, int r, LL v) {
        L[k] = l;
        R[k] = r;
        flags[k] = -1;
        if (l == r) {
            sum[k] = v;
            rights[k] = v;
            return;
        }
        int mid = (l+r) >> 1;
        Build(LS(k), l, mid, v);
        Build(RS(k), mid + 1, r, v);
        sum[k] = sum[LS(k)] + sum[RS(k)];
        rights[k] = rights[RS(k)];
    }

    void cal_and_push(int k) {
        if (flags[k] == -1) {
            return;
        }
        sum[k] = (LL)(flags[k]) * (LL)(R[k]-L[k]+1);
        rights[k] = flags[k];
        if (R[k] > L[k]) {
            flags[LS(k)] = flags[k];
            flags[RS(k)] = flags[k];
        }
        flags[k] = -1;
    }

    LL Sum(int k, int l, int r) {
        cal_and_push(k);
        if (L[k] == l && R[k] == r) {
            return sum[k];
        }
        int mid = (L[k]+R[k]) >> 1;
        if (r <= mid) return Sum(LS(k), l, r);
        else if (l > mid) return Sum(RS(k), l, r);
        return Sum(LS(k), l, mid) + Sum(RS(k), mid+1, r);
    }

    void Set(int k, int l, int r, int v) {
        if (L[k] == l && R[k] == r) {
            flags[k] = v;
            cal_and_push(k);
            return;
        }
        int mid = (L[k]+R[k]) >> 1;
        if (r <= mid) Set(LS(k), l, r, v);
        else if (l > mid) Set(RS(k), l, r, v);
        else Set(LS(k), l, mid, v), Set(RS(k), mid+1, r, v);
        sum[k] = sum[LS(k)] + sum[RS(k)];
        rights[k] = rights[RS(k)];
    }

    int LowerBound(int k, int l, int r, int v) {
        cal_and_push(k);
        if (l == r) {
            if (sum[k] < v) return r+1;
            return l;
        }
        int mid = (L[k]+R[k]) >> 1;
        if (r <= mid) return LowerBound(LS(k), l, r, v);
        else if (l > mid) return LowerBound(RS(k), l, r, v);
        else {
            cal_and_push(LS(k));
            if (rights[LS(k)] < v) {
                return LowerBound(RS(k), mid + 1, r, v);
            }
            return LowerBound(LS(k), l, mid, v);
        }
        return r+1;
    }

    void WalkPrint(int k) {
        printf("%d %d %d %d\n", k, L[k], R[k], rights[k]);
        if (L[k] == R[k]) return;
        WalkPrint(LS(k));
        WalkPrint(RS(k));
    }
};

FUNCTOR(pii_first, bool, (PII p1, PII p2), {return p1.first < p2.first;})
FUNCTOR(pii_second, bool, (PII p1, PII p2), {return p1.second < p2.second;})

void bfs(int n, int begin, VEC<int> &dis, VEC<VEC<int>> &edges) {
    queue<int> q;
    VEC<bool> vis(n+1, false);
    vis[begin] = true;
    dis[begin] = 0;
    q.push(begin);
    while (q.size() > 0) {
        int p = q.front();
        q.pop();
        auto es = edges[p];
        FOR(i, es.size()) {
            int to = es[i];
            if (vis[to]) {
                continue;
            }
            vis[to] = true;
            dis[to] = dis[p] + 1;
            q.push(to);
        }
    }
}

int main() {
    INT(n)
    INT(m)
    INT(k)
    INPUT_VEC(int, sps, k)
    VEC<VEC<int>> edges(n+1);
    FOR(i, m) {
        INT(x)
        INT(y)
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    VEC<int> to1(n+1, n*2);
    VEC<int> ton(n+1, n*2);
    bfs(n, 1, to1, edges);
    bfs(n, n, ton, edges);

    int best = n * 2;
    FOR_BE(i, 1, n+1) 
        best = min(best, to1[i] + ton[i]);
    
    VEC<PII> xs;
    FOR(i, sps.size()) {
        int id = sps[i];
        xs.push_back(PII(to1[id]-ton[id], id));
    }
    sort(xs.begin(), xs.end(), pii_first());
    VEC<int> maxs(k);
    maxs[k-1] = ton[xs[k-1].second];
    for (int i = k-2; i >= 0; i--) 
        maxs[i] = max(maxs[i+1], ton[xs[i].second]);
    int best_ton = -1;
    FOR_BE(i, 0, k-1)
        best_ton = max(best_ton, to1[xs[i].second] + maxs[i+1] + 1);

    xs.clear();
    FOR(i, sps.size()) {
        int id = sps[i];
        xs.push_back(PII(ton[id]-to1[id], id));
    }
    sort(xs.begin(), xs.end(), pii_first());
    maxs[k-1] = to1[xs[k-1].second];
    for (int i = k-2; i >= 0; i--) 
        maxs[i] = max(maxs[i+1], to1[xs[i].second]);
    int best_to1 = -1;
    FOR_BE(i, 0, k-1)
        best_to1 = max(best_to1, ton[xs[i].second] + maxs[i+1] + 1);
    
    cout << min(best_to1, min(best_ton, best)) << endl;
    return 0;
}