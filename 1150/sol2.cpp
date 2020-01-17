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
 
const int nx = 55;
const int inf = 1000000;
 
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, N, M, pair_of_right[nx], pair_of_left[nx], kun_vis[nx], vis[nx][nx];
 
vector<int> g[nx];
int id[nx][nx], dis[nx][nx], dis_to_hum[nx][nx];
vector<pair<int, int>> ghost, hum;
char grid[nx][nx];
 
bool ok(int x, int y)
{
  return 0 <= x && 0 <= y && x < n && y < n && grid[x][y] != '#' && vis[x][y] == 0;
}
 
void bfs(int s)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      vis[i][j] = 0;
      dis[i][j] = inf;
    }
 
  queue<pair<int, int> > Q;
  Q.push(ghost[s]);
  dis[ghost[s].first][ghost[s].second] = 0;
 
  while (!Q.empty()) {
    auto it = Q.front();
    Q.pop();
    for (int i = 0; i < 4; i++) {
      int x = it.first + dx[i];
      int y = it.second + dy[i];
      if (ok(x, y) && dis[x][y] > dis[it.first][it.second] + 1) {
        dis[x][y] = dis[it.first][it.second] + 1;
        vis[x][y] = 1;
        Q.push({x, y});
        if (grid[x][y] == 'H') {
          dis_to_hum[s][id[x][y]] = dis[x][y];
        }
      }
    }
  }
}
 
bool kuhn(int u)
{
  if (kun_vis[u])return 0;
  kun_vis[u] = 1;
 
  for (auto it : g[u]) {
    int v = it - N;
    if (pair_of_right[v] == -1 || kuhn(pair_of_right[v])) {
      pair_of_right[v] = u;
      pair_of_left[u] = v;
      return 1;
    }
  }
  return 0;
}
 
int max_match()
{
  for (int i = 0; i < N; i++) pair_of_left[i] = -1;
  for (int i = 0; i < M; i++) pair_of_right[i] = -1;
 
  int path_found = -1;
  do {
    path_found = 0;
    for (int i = 0; i < N; i++) kun_vis[i] = 0;
    for (int i = 0; i < N; i++) {
      if (pair_of_left[i] < 0 && kun_vis[i] == 0)
        path_found |= kuhn(i);
    }
  } while (path_found);
  int ret = 0;
  for (int i = 0; i < N; i++)
    if (pair_of_left[i] != -1) ++ret;
  return ret;
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
  //T = 1;
  for (int cs = 1; cs <= T; cs++) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%s", grid[i]);
    }
 
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 'G') {
          id[i][j] = ghost.size();
          ghost.push_back({i, j});
        }
        else if (grid[i][j] == 'H') {
          id[i][j] = hum.size();
          hum.push_back({i, j});
        }
      }
    }
 
    N = ghost.size();
    M = hum.size();
 
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        dis_to_hum[i][j] = inf;
 
    for (int i = 0; i < N; i++) bfs(i);
 
    int l = 0, h = inf, ans = -1;
    while (l <= h) {
      int m = (l + h) / 2;
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
          if (dis_to_hum[i][j] * 2 + 2 <= m) {
            g[i].push_back(j + N);
          }
        }
      }
 
      if (max_match() == M) {
        ans = m;
        h = m - 1;
      }
      else l = m + 1;
 
      for (int i = 0; i < N; i++) g[i].clear();
    }
 
    if (ans == -1) printf("Case %d: Vuter Dol Kupokat\n", cs);
    else printf("Case %d: %d\n", cs, ans);
    ghost.clear();
    hum.clear();
  }
  
