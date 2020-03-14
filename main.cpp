#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <cstring>
using namespace std;

#define MAXN 500005
#define N(n) n+20
#define LL long long
#define INT(n) int n;scanf("%d", &n);
#define INTs(xs, n) for(int i = 0; i < n; i++) scanf("%d", &xs[i]);
#define FOR(i, n) for(int i = 0; i < n; i ++)
#define FOR1(i, b, e) for(int i = b; i < e; i++)
#define FORMAP(m, it) for(auto it = m.begin(); it != m.end(); it++)
#define COPY(dst, src, n) memcpy(dst, src, sizeof((dst)[0])*n);
#define RESET(xs, n, v) for(int i = 0; i < n; i++) xs[i] = v;
#define PRTARRAY(xs, b, e) for(int i = b; i < e; i++) cout << xs[i] << " "; cout << endl;


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

int main() {
    LL l2r[MAXN];
    LL r2l[MAXN];
    int results[MAXN];
    int ms[MAXN];

    INT(n)
    FOR1(i, 1, n+1) scanf("%d", &ms[i]);
    SegmentTree st(n);

    st.Build(1, 1, n, 0);
    st.Set(1, 1, 1, ms[1]);
    l2r[1] = ms[1];
    FOR1(i, 2, n+1) {
        int lim = st.LowerBound(1, 1, i-1, ms[i]);
        st.Set(1, lim, i, ms[i]);
        l2r[i] = st.Sum(1, 1, i);
    }

    reverse(ms+1, ms+1+n);
    st.Build(1, 1, n, 0);
    st.Set(1, 1, 1, ms[1]);
    r2l[1] = ms[1];
    FOR1(i, 2, n+1) {
        int lim = st.LowerBound(1, 1, i-1, ms[i]);
        st.Set(1, lim, i, ms[i]);
        r2l[i] = st.Sum(1, 1, i);
    }
    reverse(r2l+1, r2l+1+n);
    reverse(ms+1, ms+1+n);


    LL result = 0;
    int max_idx = 0;
    FOR1(i, 1, n+1) {
        if (l2r[i] + r2l[i] - ms[i] > result) {
            result = l2r[i] + r2l[i] - ms[i];
            max_idx = i;
        }
    }

    results[max_idx] = ms[max_idx];
    FOR1(i, max_idx+1, n+1) {
        results[i] = min(results[i-1], ms[i]);
    }
    for (int i = max_idx-1; i >= 1; i--) {
        results[i] = min(results[i+1], ms[i]);
    }
    PRTARRAY(results, 1, n+1);
    return 0;
}