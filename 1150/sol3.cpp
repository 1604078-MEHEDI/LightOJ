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

//*//**___________________________________________________**/

const int N = 55;
typedef pair<int, int> pii;
pii h[N], g[N];
int w[N][N], hsz, gsz, d[N][N], n;
char mat[N][N];

int adj[N][N], deg[N], lft[N], rgt[N];

bool vis[N][N], visited[N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool bpm(int u)
{
  for (int i = 0, v; i < deg[u]; i++) {
    v = adj[u][i];
    if (visited[v]) continue;
    visited[v] = true;
    if (rgt[v] == -1 || bpm(rgt[v])) {
      rgt[v] = u;
      lft[u] = v;
      return true;
    }
  } return false;
}

int bipartiteMatching() {
  memset(lft, -1, sizeof lft);
  memset(rgt, -1, sizeof rgt);

  int cnt = 0;
  for (int i = 0; i  < hsz; i++) {
    memset(visited, false, sizeof visited);
    if (bpm(i))cnt++;
  }
  return cnt;
}

void buld_graph(int m)
{
  memset(deg, 0, sizeof deg);
  for (int i = 0; i < hsz; i++) {
    for (int j = 0; j < gsz; j++) {
      if (w[i][j] <= m) adj[i][deg[i]++] = j;
    }
  }
}

bool is_valid(int x, int y)
{
  if (x < 0 || y < 0 || x >= n || y >= n || mat[x][y] == '#' || vis[x][y])
    return false;
  return true;
}

void bfs(pii u)
{
  queue<pii> Q;
  pii v;
  memset(vis, false, sizeof vis);
  memset(d, 3, sizeof d);
  Q.push(u);
  vis[u.first][u.second] = true;
  d[u.first][u.second] = 0;

  while (!Q.empty()) {
    u = Q.front();
    Q.pop();

    for (int i = 0; i < 4; i++) {
      v.first = u.first + dx[i];
      v.second = u.second + dy[i];
      if (is_valid(v.first, v.second)) {
        d[v.first][v.second] = d[u.first][u.second] + 1;
        vis[v.first][v.second] = true;
        Q.push(v);
      }
    }
  }
}


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
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", mat[i]);
    hsz = 0;
    gsz = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (mat[i][j] == 'H') h[hsz++] = pii(i, j);
        else if (mat[i][j] == 'G') g[gsz++] = pii(i, j);
      }
    }


    for (int i = 0; i < hsz; i++) {
      bfs(h[i]);
      for (int j = 0; j < gsz; j++) {
        w[i][j] = d[g[j].first][g[j].second] * 2 + 2;
      }
    }

    int l = 0, r = 1000;
    int ans = -1;
    while (l <= r) {
      int m = (l + r) / 2;
      buld_graph(m);
      if (bipartiteMatching() == hsz) {
        r = m - 1;
        ans = m;
      }
      else l = m + 1;
    }

    printf("Case %d: ", cs);
    if (ans == -1) printf("Vuter Dol Kupokat\n");
    else printf("%d\n", ans);
  }
  return 0;
}
