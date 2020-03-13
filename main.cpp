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
#define FOR(i, n) for(int i = 0; i < n; i ++)

int main() {
    INT(n)
    int as[200005], bs[200008], xs[200009];
    INTs(as, n)
    INTs(bs, n)
    FOR(i, n) {
        xs[i] = as[i] - bs[i];
    }
    sort(xs, xs+n);
    LL sum = 0;
    int j = n;
    FOR(i, n) {
        while (j > 0 && xs[i] + xs[j-1] > 0) j--;
        if (j <= i) {
            sum += (n - i - 1);
        } else {
            sum += (n - j);
        }
    }
    printf("%lld\n", sum);
    return 0;
}