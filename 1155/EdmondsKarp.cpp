//http://lightoj.com/volume_showproblem.php?problem=1154
#include <bits/stdc++.h>
using namespace std;
#define INF 1<<30
#define endl '\n'
#define maxn 1000005
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);
const ll mod = 1e9 + 7;

inline void normal(ll &a) { a %= mod; (a < 0) && (a += mod); }
inline ll modMul(ll a, ll b) { a %= mod, b %= mod; normal(a), normal(b); return (a * b) % mod; }
inline ll modAdd(ll a, ll b) { a %= mod, b %= mod; normal(a), normal(b); return (a + b) % mod; }
inline ll modSub(ll a, ll b) { a %= mod, b %= mod; normal(a), normal(b); a -= b; normal(a); return a; }
inline ll modPow(ll b, ll p) { ll r = 1; while (p) { if (p & 1) r = modMul(r, b); b = modMul(b, b); p >>= 1; } return r; }
inline ll modInverse(ll a) { return modPow(a, mod - 2); }
inline ll modDiv(ll a, ll b) { return modMul(a, modInverse(b)); }


/**
template < typename F, typename S >
ostream& operator << ( ostream& os, const pair< F, S > & p ) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template < typename T >
ostream &operator << ( ostream & os, const vector< T > &v ) {
    os << "{";
    for (auto it = v.begin(); it != v.end(); ++it) {
        if ( it != v.begin() ) os << ", ";
        os << *it;
    }
    return os << "}";
}

template < typename T >
ostream &operator << ( ostream & os, const set< T > &v ) {
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        if ( it != v.begin()) os << ", ";
        os << *it;
    }
    return os << "]";
}

template < typename F, typename S >
ostream &operator << ( ostream & os, const map< F, S > &v ) {
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        if ( it != v.begin() ) os << ", ";
        os << it -> first << " = " << it -> second ;
    }
    return os << "]";
}

#define dbg(args...) do {cerr << #args << " : "; faltu(args); } while(0)

clock_t tStart = clock();
#define timeStamp dbg("Execution Time: ", (double)(clock() - tStart)/CLOCKS_PER_SEC)

void faltu () { cerr << endl; }

template <typename T>
void faltu( T a[], int n ) {
    for (int i = 0; i < n; ++i) cerr << a[i] << ' ';
    cerr << endl;
}

template <typename T, typename ... hello>
void faltu( T arg, const hello &... rest) { cerr << arg << ' '; faltu(rest...); }
// Program showing a policy-based data structure.
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less
#include <iostream>
using namespace __gnu_pbds;
using namespace std;
// GNU link : https://goo.gl/WVDL6g
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
        tree_order_statistics_node_update>
        new_data_set;

// find_by_order(k) – ফাংশনটি kth ordered element এর একটা পয়েন্টার রিটার্ন করে। অর্থাৎ তুমি চাইলেই kth ইন্ডেক্সে কি আছে, সেটা জেনে ফেলতে পারছো!
// order_of_key(x) – ফাংশনটি x এলিমেন্টটা কোন পজিশনে আছে সেটা বলে দেয়।

*////*___________________________________________________**/

const int inf = 1e9;
const int eps = 1e-6;
const int N = 405;
int capacity[N][N];
//int flow[N][N];
vector<int> graph[N];
bool vis[N];
int parent[N];
int a[N];
int residualCapacity[N][N];

bool bfs(int s, int t)
{
  for (int i = 0; i < N; i++) parent[i] = i;
  memset(vis, 0, sizeof vis);
  queue<int> Q;
  Q.push(s);
  vis[s] = 1;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (auto v : graph[u]) {
      if (!vis[v] && residualCapacity[u][v]) {
        parent[v] = u;
        Q.push(v);
        vis[v] = 1;
      }
    }
  }
  return vis[t];
}

int EdmondsKarp(int s, int t)
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      residualCapacity[i][j] = capacity[i][j];

  int ans = 0;
  int flow;
  while (bfs(s, t)) {
    flow = INT_MAX;
    int cur = t;
    while (cur != s) {
      flow = min(flow, residualCapacity[parent[cur]][cur]);
      cur = parent[cur];
    }
    ans += flow;
    cur = t;
    while (cur != s) {
      residualCapacity[parent[cur]][cur] -= flow;
      residualCapacity[cur][parent[cur]] += flow;
      cur = parent[cur];
    }
  }
  return ans;
}

void addEdge(int u, int v)
{
  graph[u].push_back(v);
  graph[v].push_back(u);
}

struct info
{
  int x, y, n, m;
  info() {}
  info(int a, int b, int c, int d) {x = a, y = b, n = c, m = d;}
};


int main()
{
  //FASTIO
  ///*
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  freopen("error.txt", "w", stderr);
#endif
  //*/
  int T;
  scanf("%d", &T);
  for (int cs = 1; cs <= T; cs++) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      capacity[i][n + i] += a[i];
      graph[i].push_back(n + i);
      graph[n + i].push_back(i);
    }
    int s = 2 * n + 1;
    int t = s + 2;
    int m;
    scanf("%d", &m);
    while (m--) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      graph[n + u].push_back(v);
      graph[v].push_back(n + u);
      capacity[n + u][v] += w;
    }
    int D, B;
    scanf("%d %d", &B, &D);
    while (B--) {
      int x;
      scanf("%d", &x);
      graph[s].push_back(x);
      graph[x].push_back(s);
      capacity[s][x] = inf;
    }

    while (D--) {
      int x;
      scanf("%d", &x);
      graph[n + x].push_back(t);
      graph[t].push_back(n + s);
      capacity[n + x][t] = inf;
    }
    int ans = EdmondsKarp(s, t);
    printf("Case %d: %d\n", cs, ans);
    for (int i = 0; i <= n * 2; i++) graph[i].clear();
    memset(capacity, 0, sizeof capacity);
  }
  return 0;
}
