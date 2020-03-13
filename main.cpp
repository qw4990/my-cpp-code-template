#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#define INT(n) int n;scanf("%d", &n);
#define INTs(xs, n) for(int i = 0; i < n; i++) scanf("%d", &xs[i]);
#define FOR(i, n) for(int i = 0; i < n; i ++)

int main() {
    INT(t)
    int as[200005];
    FOR(cas, t) {
        INT(n)
        INTs(as, 2*n)
        sort(as, as+2*n);
        printf("%d\n", abs(as[n-1]-as[n]));
    }
    return 0;
}