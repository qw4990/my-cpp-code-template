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
#define INPUT_VEC(vs, n) vs.resize(n); for(int i = 0; i < n; i++) cin >> vs[i];
#define OUTPUT_VEC(vs) for(auto it=vs.begin(); it != vs.end(); it++) cout << *it << " "; cout << endl;
#define OUTPUT_BE(begin, end) for(auto it = begin; it != end; it++) cout << *it << " "; cout << endl;
#define FUNCTOR(name, ret, args, body) struct name {ret operator() args body};
#define CLOCK_BEGIN() clock_t _clock_begin_ = clock();
#define CLOCK_END() clock_t _clock_end_ = clock(); cout << "clock" << ": " << 1000*((double)(_clock_end_-_clock_begin_)/CLOCKS_PER_SEC) << "ms" << endl;

#define PII pair<int, int>
#define PLL pair<long long, long long>
FUNCTOR(pii_first, bool, (PII p1, PII p2), {return p1.first < p2.first;})
FUNCTOR(pii_second, bool, (PII p1, PII p2), {return p1.second < p2.second;})

VEC<LL> vs;

int main() {
    vs.resize(100009);
    vs[0] = 0;
    FOR(i, 1, 1e5) vs[i]=vs[i-1]+i;

    FORCASE() {
        LL n, k;
        cin >> n >> k;

        auto it = lower_bound(vs.begin(), vs.end(), k);
        int idx = it - vs.begin();
        int x = vs[idx]-k;

        REP(i, n-idx-1) cout << 'a';
        cout << 'b';
        REP(i, x) cout << 'a';
        cout << 'b';
        REP(i, idx-x-1) cout << 'a';
        cout << endl;


        /*
            aaaaaaabb  c(1,1) 1   1
            aaaaaab..  c(2,1) 2   3
            aaaaab...  c(3,1) 3   6
            aaaab....
            aaab.....
            aab......

            x - a
            2 - b

            a ..... C(x+1, 2)
            b .....

        */
    }
    return 0;
}