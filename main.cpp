#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <cstring>
using namespace std;

#define LL long long
#define INT(n) int n;scanf("%d", &n);
#define INTs(xs, n) for(int i = 0; i < n; i++) scanf("%d", &xs[i]);
#define FOR(i, n) for(int i = 0; i < n; i ++)
#define FOR1(i, b, e) for(int i = b; i < e; i++)
#define FORMAP(m, it) for(auto it = m.begin(); it != m.end(); it++)
#define COPY(dst, src, n) memcpy(dst, src, sizeof((dst)[0])*n);
#define RESET(xs, n, v) for(int i = 0; i < n; i++) xs[i] = v;

int main() {
    INT(n)
    int bs[200006], xs[200006];
    INTs(bs, n)
    FOR(i, n) xs[i] = bs[i]-i;
    map<int, LL> m;
    m[xs[0]] = bs[0];
    FOR1(i, 1, n) m[xs[i]] += bs[i];
    LL ret = 0;
    FORMAP(m, it) ret = max(ret, it->second);
    printf("%lld\n", ret);
    return 0;
}