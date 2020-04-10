/*

https://codeforces.com/contest/1333/problem/D

可以把 RL 的转向，看成交换他俩的位置，这样模型会清晰很多。
于是可以发现，我们的操作就是把所有的 L 移动到最左边。

我们可以先计算能够移动的最大次数 tot，等于每个 L 左边的 R 的个数累加和。
能够移动的最小次数不能直接算出，但是可以贪心，每次尽量移动多的 L。

有了上述条件，我们可以，先计算出 tot。
如果 k > tot，那直接输出 -1。
接下来模拟 k 步。

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

*/