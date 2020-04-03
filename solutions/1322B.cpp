/*

题目：https://codeforces.ml/problemset/problem/1322/B

解法 1：
拆位处理，先求最后一位是不是 1，再求倒数第二位是不是 1，以此类推。
计算低 k 位是不是 1 的方法，就是对于每个数 a，求和他相加后这一位为 1 的 count，然后把所有 count 相加。
如果 sum_count&1 == 1，则说明这一位是 1。

对于每次处理 a 的 k 位，如果
1. a[k]==1：则和他相加后 k 为 1 的数 b 有两种情况：
    1）b[k]==0 且 b[0:k-1]+a[0:k-1] 不会产生进位
    2）b[k]==1 且 b[0:k-1]+a[0:k-1] 会有进位
2. a[k]==0：则同样 b 有两种情况：
    1）b[k]==0 且 b[0:k-1]+a[0:k-1] 会产生进位
    2）b[k]==1 且 b[0:k-1]+a[0:k-1] 不会有进位
为了快速处理满足 a[k] 条件的 b 有多少个，把所有的 b 安位拆分后维护在一棵二叉树上。
二叉树的边表示某一位是 0 还是 1，节点维护一个 sum 表示进过改点的个数。

最后的复杂度为 O(logA*logA*n): 不过很可惜最后 TLE 了

int n;
VEC<int> as;

struct node {
    VEC<int> son;
    int sum;
};

int cur = 0;
node tree[400009*26];

int new_node() {
    tree[cur].son.resize(2);
    tree[cur].son[0] = -1;
    tree[cur].son[1] = -1;
    tree[cur].sum = 0;
    return cur++;
}

void rm_tree() {
    cur = 0;
}

void insert_tree(int nd, int v, int k) {
    tree[nd].sum++;
    if (k == -1) return;
    int b = (v >> k) & 1;
    if (b == 0) {
        if (tree[nd].son[0] == -1) tree[nd].son[0] = new_node();
        insert_tree(tree[nd].son[0], v, k-1);
    } else {
        if (tree[nd].son[1] == -1) tree[nd].son[1] = new_node();
        insert_tree(tree[nd].son[1], v, k-1);
    }
    return;
}

int find_push(int nd, int v, int k) {
    if (nd == -1 || k == -1) return 0;
    int b = (v >> k) & 1;
    int ret = 0;
    if (b == 1 && tree[nd].son[1] != -1) {
        ret += tree[tree[nd].son[1]].sum;
    }
    return ret + find_push(tree[nd].son[!b], v, k-1);
}

int find_nonpush(int nd, int v, int k) {
    if (nd == -1) return 0;
    if (k == -1) return tree[nd].sum;
    int b = (v >> k) & 1;
    int ret = 0;
    if (b == 0 && tree[nd].son[0] != -1) {
        ret += tree[tree[nd].son[0]].sum;
    }
    return ret + find_nonpush(tree[nd].son[!b], v, k-1);
}

int main() {
    cin >> n;
    INPUT_VEC(as, n)

    int result = 0;
    REP(k, 26) {
        int cnt = 0;
        int root = new_node();
        FOREACH(a, as) {
            int b = (a >> k) & 1;
            cnt += find_push(tree[root].son[b], a, k-1);
            cnt += find_nonpush(tree[root].son[!b], a, k-1);
            insert_tree(root, a, k);
        }
        if (cnt & 1) result += (1 << k);
        rm_tree();
    }
    cout << result << endl;
    return 0;
}

*/

/*

解法 2：
分开处理每个二进制位 k，设置 bit = (1<<k)。
按照每个数 a&bit 的结果分为 ones 和 zeros。
分别处理 zeros 内，zeros 和 ones 之间，ones 内相加后第 k 位为 1 的个数，然后看个数是奇数还是偶数。
可以先对 ones 和 zeros 排序，就会发现单调性，然后用双指针解决。

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
*/