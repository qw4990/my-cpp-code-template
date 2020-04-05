#include "defines.h"

class lca {
public:
    int n, base;
    VEC<int> deep;
    VEC<VEC<int>> dp;

    lca(int root, const VEC<VEC<int>> &egs) {
        n = egs.size() + 1;
        deep.resize(n + 1); // starts from 1
        dp.resize(n + 1);
        base = 1;
        while ((1<<base) <= n) base++;
        FOR(i, 1, n) dp[i].resize(base+1, 0);
        deep[0] = 0;
        dfsinit(1, 0, egs);
    }

    void dfsinit(int u, int fa, const VEC<VEC<int>> &egs) {
        deep[u] = deep[fa]+1;
        dp[u][0] = fa;
        for (int i = 1; (1<<i) <= deep[u]; i++) 
            dp[u][i] = dp[dp[u][i-1]][i-1];
        FOREACH(v, egs[u]) {
            if (v == fa) continue;
            dfsinit(v, u, egs);
        } 
    }

    int get_lca(int u, int v) {
        if (deep[u] < deep[v]) swap(u, v);
        for (int i = base; i >= 0; i--) {
            if (dp[u][i] == 0) continue;
            int x = dp[u][i];
            if (deep[x] >= deep[v]) u = x;
        }
        if (u == v) return u;
        for (int i = base; i >= 0; i--) {
            if (dp[u][i] == 0) continue;
            if (dp[u][i] != dp[v][i]) {
                u = dp[u][i];
                v = dp[v][i];
            }
        }
        return dp[u][0];
    }
};
