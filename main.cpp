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

int n;
VEC<int> as, zero, one;

int main() {
    cin >> n;
    INPUT_VEC(as, n)

    int anw = 0;
    REP(k, 26) {
        zero.clear();
        one.clear();
        int mask = (1<<(k+1))-1, bit = (1<<k);
        FOREACH(a, as) {
            if (a & bit) {
                one.push_back(a&mask);
            } else {
                zero.push_back(a&mask);
            }
        }

        sort(zero.begin(), zero.end());
        sort(one.begin(), one.end());

        int cnt = 0;
        int j = zero.size();
        REP(i, int(zero.size())-1) { // 0&0
            while (j-1 > i && ((zero[j-1] + zero[i])&bit)) j--;
            if (j <= i) j++;

            cnt += (zero.size() - j);
        }

        j = one.size();
        REP(i, zero.size()) { // 0&1
            while (j-1 >= 0 && !((one[j-1] + zero[i])&bit)) j--;
            cnt += j;
        }

        j = one.size();
        REP(i, int(one.size())-1) {// 1&1
            while (j-1 > i && ((one[j-1] + one[i])&bit)) {j--;}
            if (j <= i) j++;
            cnt += (one.size() - j);
        }

        if (cnt & 1) anw += bit;
    }

    cout << anw << endl;
    return 0;
}