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
     
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    const int N = 55;
    int l[N], r[N], seen[N], deg[N], adj[N], n, mark[N][N];
    char grid[N][N];
    int vis[N][N];
    vector<pair<int, int> > graph[N];
     
    bool is_valid(int x, int y, int mk)
    {
      if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] == '#' || vis[x][y] == mk) return 0;
      return 1;
    }
     
    void bfs(int x, int y, int k, int d)
    {
      queue<pair<int, int>> Q;
      queue<int> dis;
      Q.push({x, y});
      dis.push(0);
     
      while (!Q.empty()) {
        auto nw = Q.front();
        Q.pop();
        int w = dis.front();
        dis.pop();
        if (grid[nw.first][nw.second] == 'G') {
          graph[k].push_back({w, mark[nw.first][nw.second]});
        }
     
        for (int i = 0; i < 4; i++) {
          int r = nw.first + dx[i];
          int c = nw.second + dy[i];
          if (is_valid(r, c, k)) {
            vis[r][c] = k;
            Q.push({r, c});
            dis.push(w + 1);
          }
        }
      }
    }
     
    void init(int h)
    {
      for (int i = 0; i <= h; i++) graph[i].clear();
    }
     
    bool bpm(int x, int lmt) {
    // dbg(x, lmt);
      for (auto it : graph[x]) {
        int u = it.first;
        int v = it.second;
        if (u > lmt || seen[v]) continue;
        seen[v] = 1;
        if (r[v] == -1 || bpm(r[v], lmt)) {
          r[v] = x;
          return 1;
        }
      }
      return 0;
    }
     
    bool solve(int dis, int h)
    {
      //dbg(dis, h);
      memset(r, -1, sizeof r);
      for (int i = 1; i <= h; i++) {
        memset(seen, 0, sizeof seen);
        if (bpm(i, dis) == 0) return 0;
      }
      return 1;
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
        memset(mark, 0, sizeof mark);
        memset(vis, 0, sizeof vis);
        int g = 0, h = 0;
        for (int i = 0; i < n; i++) {
          scanf("%s", grid[i]);
          for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'H') mark[i][j] = ++h;
            if (grid[i][j] == 'G') mark[i][j] = ++g;
          }
        }
        init(h);
     
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
     
            if (grid[i][j] == 'H') {
              // dbg(grid[i][j]);
              bfs(i, j, mark[i][j], 0);
            }
          }
        }
        //dbg(h,g);
        int mx = -1;
        int lo = 0, hi = 100000;
        while (lo <= hi) {
          int  m = (lo  + hi) / 2;
          //dbg(m);
          if (solve(m, h)) {
            mx = m;
            //dbg(m);
            hi = m - 1;
          }
          else {
            lo = m + 1;
          }
        }
        //dbg(mx);
        if (mx == -1) {
          printf("Case %d: Vuter Dol Kupokat\n", cs);
        }
        else {
          int ans = 2 * mx + 2;
          printf("Case %d: %d\n", cs, ans);
        }
      }
      return 0;
    }
