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
#include <stack>
#include <deque>
#include <list>
#include <math.h>
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
#define MATRIX(T, ma, n, m) vector<vector<T>> ma(n, vector<T>(m));
#define INPUT_VEC(vs, n) vs.resize(n); for(int i = 0; i < n; i++) cin >> vs[i];
#define OUTPUT_VEC(vs) for(auto it=vs.begin(); it != vs.end(); it++) cout << *it << " "; cout << endl;
#define OUTPUT_BE(begin, end) for(auto it = begin; it != end; it++) cout << *it << " "; cout << endl;
#define PII pair<int, int>
#define PLL pair<long long, long long>
#define FUNCTOR(name, ret, args, body) struct name {ret operator() args body};
#define PQ priority_queue
#define CLOCK_BEGIN() clock_t _clock_begin_ = clock();
#define CLOCK_END() clock_t _clock_end_ = clock(); cout << "clock" << ": " << 1000*((double)(_clock_end_-_clock_begin_)/CLOCKS_PER_SEC) << "ms" << endl;


FUNCTOR(pii_first, bool, (PII p1, PII p2), {return p1.first < p2.first;})
FUNCTOR(pii_second, bool, (PII p1, PII p2), {return p1.second < p2.second;})

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

// calculate (x^n)%mod.
// O(log(n))
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

// a*result = 1(%mod), the mod must be a prime number.
// Fermat's little theorem: a%(prime-1) = 1(%prime) ==> the result is a^(prime-2)%prime.
// O(log(prime_mod)).
LL ModInverse(int a, LL prime_mod) {
    return FastMultiplyMod(a, prime_mod-2, prime_mod);
}

// C(a, b), a = 5, b = 2 ==> 10.
// Calculate all combination numbers and store them in results.
// Pascal's traingle: C(a, b) = C(a-1, b-1) + C(a-1, b).
// O(a*b)
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

// C(a, b), a = 5, b = 2 ==> 10, the mod number must be prime. 
// C(a, b) = a!/(b!*(a-b)!)
// O(log(mod))
LL CombinationModWithFactors(int a, int b, VEC<LL> &factors, LL prime_mod) {
    return (factors[a] * ModInverse((factors[b] * factors[a-b]) % prime_mod, prime_mod)) % prime_mod;
}

// Calculate 1!, 2!, ... n! and store them in the fac vector. 
// O(n)
void Factorial(int n, VEC<LL> &fac, LL mod) {
    fac.resize(n+1);
    fac[1] = 1;
    FOR(i, 2, n) fac[i] = (fac[i-1] * i) % mod;
}

// Calculate the greatest common divisor. 
// gcd(a, b) = gcd(b, a%b).
// O(log(min(a, b)))
LL GCD(LL a, LL b) {
    if (a % b == 0) return b;
    return GCD(b, a%b);
}

// Factoring the x. 
// for example: 2484 = 2 * 2 * 3 * 3 * 3 * 23
// O(sqrt(x))
void Factoring(LL x, VEC<LL> &factors) {
    LL prim = 2;
    while (prim * prim <= x) {
        while (x % prim == 0) {
            factors.push_back(prim);
            x /= prim;
        }
        prim ++;
    }
    if (x != 1) factors.push_back(x);
}

// IsPrime tests if this number is a prime number.
// O(sqrt(x))
bool IsPrime(LL x) {
    if (x <= 1) return false;
    for (LL i = 2; i*i <= x; i++) 
        if (x % i == 0) return false;
    return true;
}

// ##################################################################
// ############################ strings ############################
// ##################################################################

// Calculate the next vector used by KMP Algorithm.
// str:  a b a b a b z a b a b a b a
// next: 0 0 1 2 3 4 0 1 2 3 4 5 6 ?
void kmpNext(VEC<char> &str, VEC<int> &next) {
    int n = str.size();
    next.resize(n-1);
    next[0] = 0;
    int max_len = 0;
    FOR(i, 1, n-1) {
        while (max_len > 0 && str[i] != str[max_len])
            max_len = next[max_len - 1];
        if (str[max_len] == str[i]) max_len++;
        next[i] = max_len;
    }
}

// The KMP Algorithm.
// str:         a b a b a b z a b a b a b
// substr:      a b a
// position:    0   2         7   9
void kmp(VEC<char> &str, VEC<char> &substr, VEC<int> &position) {
    VEC<int> next;
    kmpNext(substr, next);
    position.clear();
    int n = str.size(), max_len = 0;
    REP(i, n) {
        while (max_len > 0 && str[i] != substr[max_len])
            max_len = next[max_len - 1];
        if (str[i] == substr[max_len]) max_len ++;
        if (max_len == substr.size()) {
            position.push_back(i - substr.size() + 1);
            max_len = next[max_len - 1];
        }
    }
}

// Manacher algorithm is used to calculate palindrome strings.
// All int elements in the original str vectors should be larger than 0.
// If the input str is "a b c c b c a", then the output are:
//  manastr: ^ a # b # c # c # b # c # a # $
//  manapal: 0 0 0 1 0 1 4 1 0 3 0 1 0 1 0 0
void manacher(VEC<char> &str, VEC<char> &manastr, VEC<int> &manapal) {
    // prepare
    manastr.clear();
    manastr.push_back('^');
    FOREACH(x, str) {
        manastr.push_back(x);
        manastr.push_back('#');
    }
    manastr.push_back('$');
    
    // calculate manapal
    int n = manastr.size();
    manapal.resize(n);
    int center = 0, right = 0;
    FOR(i, 1, n-1) {
        int i_mirror = 2 * center - i;
        if (right > i) manapal[i] = min(right - i, manapal[i_mirror]);
        else manapal[i] = 0;
        
        while (manastr[i + 1 + manapal[i]] == manastr[i - 1 - manapal[i]])
            manapal[i]++;
        
        if (i + manapal[i] > right) {
            center = i;
            right = i + manapal[i];
        }
    }
}

// ##################################################################
// ########################### CODE BELOW ###########################
// ##################################################################

int main() {
    return 0;
}