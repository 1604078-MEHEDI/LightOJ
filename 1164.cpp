#include <bits/stdc++.h>
using namespace std;
#define INF 1<<30
#define endl '\n'
#define maxn 100005
#define tc printf("Case %d: ", cs)
#define tcn printf("Case %d:\n", cs);
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);
#define dbg(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

ll a[maxn];
ll tree[maxn * 3], lazy[maxn * 3];

void build_tree(int node, int l, int r)
{
    if (l > r) return;
    if (l == r) { // leaf node
        tree[node] = a[l];
        return;
    }

    build_tree(node * 2, l, (l + r) / 2);
    build_tree(2 * node + 1, (l + r) / 2 + 1, r);
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]);
}

void update_tree(int node, int l, int r, int i, int j, ll val)
{
    if (lazy[node] != 0) {
        tree[node] += lazy[node] * (r - l + 1);
        if (l != r) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (l > r || l > j || r < i) return;

    if (l >= i && r <= j) { //segment fully range
        tree[node] += val * (r - l + 1);

        if (l != r) {// Not leaf node
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        return;
    }

    update_tree(2 * node, l, (l + r) / 2, i, j, val);
    update_tree( 2 * node + 1, 1 + (l + r) / 2, r,  i, j, val);
    tree[node] = (tree[node * 2] + tree[node * 2 + 1]) + (r -l + 1) * lazy[node];
}

ll query_tree(int node, int l, int r, int i, int j)
{
    if (l > j || r < i) return 0;

    if (lazy[node] != 0) {
        tree[node] += lazy[node] * (r - l + 1);

        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (l >= i && r <= j) return tree[node];

    ll q1 = query_tree(node * 2, l, (l + r) / 2, i, j);
    ll q2 = query_tree(1 + node * 2, 1 + ((l + r) / 2), r, i, j);
    ll ans = (q1 + q2);
    return ans;
}


int main()
{
    FASTIO
    ///*
    //double start_time = clock();
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
//*/
    int T;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; cs++) {
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof lazy);
        int n, q;
        scanf("%d %d", &n, &q);
        for (int i = 0; i < n; i++)a[i] = 0;
        build_tree(1, 0, n - 1);
        printf("Case %d:\n", cs);
        while (q--) {
            int x;
            scanf("%d", &x);
            if (x) {
                int l, r;
                scanf("%d %d", &l, &r);
                printf("%lld\n", query_tree(1, 0, n - 1, l, r));
            }
            else {
                int l, r, val;
                scanf("%d %d %d", &l, &r, &val);
                update_tree(1, 0, n - 1, l, r, val);
            }
        }
    }

    //double end_time = clock();
    //printf( "Time = %lf ms\n", ( (end_time - start_time) / CLOCKS_PER_SEC)*1000);
    return 0;
}
