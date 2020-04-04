/*

题目：https://codeforces.ml/contest/1329/problem/C

可以发现如果不考虑平衡性，一直从根节点开始弹出节点，最后数字是最优的。
为了考虑平衡性，我们可以用贪心的方式来：
1. 一直尝试从根节点弹出，直到可能出现不平衡；
2. 递归的去弹出根节点下一级的左右儿子节点；

保证平衡的条件是：最多弹出到 g 层；
每次尝试弹出，就是从当前根节点，不断向下找到要弹出的值，且判断一下是否会造成不平衡。
每次尝试弹出的复杂度为 O(logn)，最多弹 n 下，则总复杂度为 O(nlogn)。

下面直接是代码，其实很简单。

int h, g;
VEC<int> as, anw;
 
inline int rm(int nd, int deep) {
    if (deep == g && as[nd*2] == 0 && as[(nd*2)+1] == 0) {
        return -1;
    }
    if (as[nd*2] == 0 && as[(nd*2)+1] == 0) {
        int x = as[nd];
        as[nd] = 0;
        return x;
    }
 
    int x = -1;
    if (as[nd*2] > as[(nd*2)+1]) {
        x = rm(nd*2, deep+1);
    } else {
        x = rm((nd*2)+1, deep+1);
    }
    if (x != -1) {
        int y = as[nd];
        as[nd] = x;
        return y;
    }
    return -1;
}
 
void solve(int nd, int deep) {
    if (deep > g) return;
    while (rm(nd, deep) >= 0) {
        anw.push_back(nd);
    };
    solve(nd*2, deep+1);
    solve((nd*2)+1, deep+1);
}
 
int main() {
    as.resize((1<<21)+10);
    FORCASE() {
        cin >> h >> g;
        FOR(i, 1, (1<<h)-1) scanf("%d", &as[i]);
        FOR(i, (1<<h), (1<<h)*2) as[i] = 0;
 
        anw.clear();
        solve(1, 1);
 
        LL sum = 0;
        FOR(i, 1, (1<<g)-1) sum += as[i];
        cout << sum << endl;
        REP(i, anw.size()) printf("%d ", anw[i]);
        cout << endl;
    }
    return 0;
}

*/