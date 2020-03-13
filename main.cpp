#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <cstring>
using namespace std;

#define INT(n) int n;scanf("%d", &n);
#define INTs(xs, n) for(int i = 0; i < n; i++) scanf("%d", &xs[i]);
#define FOR(i, n) for(int i = 0; i < n; i ++)

int main() {
    INT(t)
    char as[101], bs[101], cs[101];
    FOR(cas, t) {
        scanf("%s", as);
        scanf("%s", bs);
        scanf("%s", cs);
        int n = strlen(as);
        bool ok = true;
        FOR(i, n) {
            if (cs[i] == as[i] || cs[i] == bs[i]) {
                continue;
            }
            ok = false;
            break;
        }
        if (ok) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}