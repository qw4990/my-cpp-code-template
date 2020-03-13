#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
using namespace std;

#define LL long long
#define INT(n) int n;scanf("%d", &n);
#define INTs(xs, n) for(int i = 0; i < n; i++) scanf("%d", &xs[i]);
#define F0R(i, n) for(int i = 0; i < n; i ++)
#define FOR(i, b, e) for(int i = b; i < e; i++)
#define COPY(dst, src, n) memcpy(dst, src, sizeof((dst)[0])*n);
#define RESET(xs, n, v) for(int i = 0; i < n; i++) xs[i] = v;

int main() {
    INT(t)
    char s[5005], tmp[5005], best[5005];
    F0R(cas, t) {
        INT(n)
        scanf("%s", s);
        int bestk = -1;
        FOR(k, 1, n+1) {
            COPY(tmp, s+k-1, n-k+1)
            COPY(tmp+n-k+1, s, k-1)
            tmp[n] = '\0';
            if ((n-k+1)&1) {
                reverse(tmp+n-k+1, tmp+n);
            }
            if (bestk == -1 || (strcmp(tmp, best) < 0)) {
                bestk = k;
                COPY(best, tmp, n)
                best[n] = '\0';
            }
        }
        printf("%s\n", best);
        printf("%d\n", bestk);
    }
    return 0;
}