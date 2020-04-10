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
#include <assert.h>
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

int n, k;
VEC<char> ds;
queue<int> pos;
VEC<VEC<int>> anws;

int main() {
    cin >> n >> k;
    ds.resize(n+1);
    FOR(i, 1, n) cin >> ds[i];

    int tot = 0, numR = 0;
    FOR(i, 1, n) {
        if (ds[i] == 'L') tot += numR;
        else numR++;
    }

    if (k > tot) {
        cout << -1 << endl;
        return 0;
    }

    while (!pos.empty()) pos.pop();
    FOR(i, 1, n-1) 
        if (ds[i] == 'R' && ds[i+1] == 'L') pos.push(i);
    REP(i, k) {
        int t = min(int(pos.size()), tot-(k-i-1));
        VEC<int> anw;
        REP(j, t) {
            int x = pos.front();
            pos.pop();
            anw.push_back(x);
            swap(ds[x], ds[x+1]);
            if (x-1>=1 && ds[x-1]=='R') pos.push(x-1);
            if (x+2<=n && ds[x+2]=='L') pos.push(x+1);
        }
        anws.push_back(anw);
        tot-=t;
    }

    if (tot > 0) {
        cout << -1 << endl;
        return 0;
    }

    REP(i, k) {
        printf("%d ", int(anws[i].size()));
        FOREACH(x, anws[i]) printf("%d ", x);
        printf("\n");
    }

    return 0;
}