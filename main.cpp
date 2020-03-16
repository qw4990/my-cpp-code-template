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
#define REP(i, n) for(int i = 0; i < n; i ++)
#define FOR(i, b, e) for(int i = b; i <= e; i++)
#define FORIT(begin, end) for(auto it = begin; it != end; it++)
#define FOREACH(x, xs) for(auto x : xs)
#define FORCASE() int _t_; cin >> _t_; for(int _i_ = 0; _i_ < _t_; _i_++)
#define COPY(dst, src, n) for(int i = 0; i < n; i++) {*dst=*src;dst++;src++;}
#define RESET(begin, end, v) for(auto it = begin; it != end; it++) *it=v;
#define VEC vector
#define INPUT_VEC(vs, n) vs.resize(n); for(int i = 0; i < n; i++) cin >> vs[i];
#define OUTPUT_VEC(vs) for(auto it=vs.begin(); it != vs.end(); it++) cout << *it << " "; cout << endl;
#define OUTPUT_BE(begin, end) for(auto it = begin; it != end; it++) cout << *it << " "; cout << endl;
#define PII pair<int, int>
#define FUNCTOR(name, ret, args, body) struct name {ret operator() args body};
#define PQ priority_queue
#define CLOCK_BEGIN() clock_t _clock_begin_ = clock();
#define CLOCK_END() clock_t _clock_end_ = clock(); cout << "clock" << ": " << 1000*((double)(_clock_end_-_clock_begin_)/CLOCKS_PER_SEC) << "ms" << endl;

// ##################################################################
// ######################## data structures #########################
// ##################################################################

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

// ##################################################################
// ############################# others #############################
// ##################################################################

void BasicBFS(int n, int begin, VEC<int> &dis, VEC<VEC<int>> &edges) {
    queue<int> q;
    VEC<bool> vis(n+1, false);
    vis[begin] = true;
    dis[begin] = 0;
    q.push(begin);
    while (q.size() > 0) {
        int p = q.front();
        q.pop();
        auto es = edges[p];
        REP(i, es.size()) {
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

// ##################################################################
// ######################### number theory ##########################
// ##################################################################

// (x^n)%mod
LL FastMultiplyMod(LL x, LL n, LL mod) {
    LL result = 1;
    LL tmp = x;
    while (n > 0) {
        if (n & 1) result = (result * tmp) % mod;
        tmp = (tmp * tmp) % mod;
        n >>= 1;
    }
    return result;
}

// a*result = 1(%mod), the mod must be a prime number
// Fermat's little theorem: a%(prime-1) = 1(%prime) ==> the result is a^(prime-2)%prime
LL ModInverse(int a, LL prime_mod) {
    return FastMultiplyMod(a, prime_mod-2, prime_mod);
}

// C(a, b), a = 5, b = 2 ==> 10
// Calculate all combination numbers and store them in results.
// Pascal's traingle: C(a, b) = C(a-1, b-1) + C(a-1, b), and then
LL FullCombinationMod(int a, int b, LL **results, LL mod) {
    if (results != 0 && results[a][b] != -1) return results[a][b];
    LL ret;
    if (b == 0 || b == a) {
        ret = 1 % mod;
    } else {
        ret = (FullCombinationMod(a-1, b, results, mod) + 
        FullCombinationMod(a-1, b-1, results, mod)) % mod;
    }
    if (results != 0) results[a][b] = ret;
    return ret;
}

// C(a, b), a = 5, b = 2 ==> 10
// C(a, b) = a!/(b!*(a-b)!)
LL CombinationModWithFactors(int a, int b, VEC<LL> &factors, LL mod) {
    return (factors[a] * ModInverse((factors[b] * factors[a-b]) % mod, mod)) % mod;
}

// Calculate 1!, 2!, ... n! and store them in the fac vector.
void FillFactorial(int n, VEC<LL> &fac, LL mod) {
    fac.resize(n+1);
    fac[1] = 1;
    FOR(i, 2, n) fac[i] = (fac[i-1] * i) % mod;
}

// Calculate the greatest common divisor.
// gcd(a, b) = gcd(b, a%b).
LL GCD(LL a, LL b) {
    if (a % b == 0) return b;
    return GCD(b, a%b);
}

// ##################################################################
// ########################### CODE BELOW ###########################
// ##################################################################

int main() {
    FORCASE() {
        int n;
        cin >> n;
        VEC<int> as;
        INPUT_VEC(as, n)
        sort(as.begin(), as.end());
        reverse(as.begin(), as.end());
        OUTPUT_VEC(as)
    }
    return 0;
}