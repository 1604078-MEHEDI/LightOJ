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

#define dbg1(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
#define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

const int N = 1005;
struct Edge
{
    int u, v, w;
    Edge() {}
    Edge(int _u, int _v, int _w) {u = _u, v = _v, w = _w;}
};
int n, m, root;
int vist[N], par[N];
int idx[N];
int dist[N]; // lowest incoming edge of a root
vector<Edge> graph;

void DMST()
{
    int res = 0, u, v, w;
    while (1) {
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            vist[i] = -1;
            idx[i] = -1;
        }

        for (int i = 0; i < m; i++) {
            u = graph[i].u;
            v = graph[i].v;
            w = graph[i].w;
            if (u != v && dist[v] > w) {
                par[v] = u;
                dist[v] = w;
            }
        }
        par[root] = root;
        dist[root] = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF) {
                puts("impossible");
                return;
            }
            res += dist[i];
        }

        int id = 0;

        //cycle detection
        for (int i = 0; i < n; i++) {
            if (vist[i] == -1) {
                int cur = i;
                while (vist[cur] == -1) {
                    vist[cur] = i;
                    cur = par[cur];
                }
                if (cur == root || vist[cur] != i)continue;// no cycle
                idx[cur] = id;
                for (u = par[cur]; cur != u; u = par[u])
                    idx[u] = id;
                id++;
            }
        }
        if (id == 0) break;//no cycle
        for (int i = 0; i < n; i++) {
            if (idx[i] == -1) // yet not find any group
            {
                idx[i] = id++;
            }
        }
        for (int i = 0; i < m; i++) {
            graph[i].w -= dist[graph[i].v];
            graph[i].u = idx[graph[i].u];
            graph[i].v = idx[graph[i].v];
        }
        n = id++;
        root = idx[root];
    }
    printf("%d\n", res);
}

int main()
{
    FASTIO
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
        scanf("%d%d%d", &n, &m, &root);
        graph.clear();
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            graph.push_back(Edge(u, v, w));
        }
        printf("Case %d: ", cs);
        DMST();
    }
    return 0;
}
/******************************************************************************************************************/
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

#define dbg1(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
#define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

typedef pair<int, int> pii;
const int N = 1005;
int col[2 * N];

bool findCycle(int u, const vector<vector<pii> > &graph, vector<int> &cycle)
{
  col[u] = 1;
  for (auto x : graph[u]) {
    if (x.second || u == x.first) continue;
    int v = x.first;
    if (col[v] == 0) {
      bool found = findCycle(v, graph, cycle);
      if (!found)continue;
      if ((int)cycle.size() > 1 && cycle[0] == cycle.back())
        return true;
      cycle.push_back(v);
      return true;
    }
    else if (col[v] == 1) {
      cycle.push_back(v);
      return true;
    }
  }
  col[u] = 2;
  return false;
}

int minCostArborescense(vector<vector<pii> > &graph, int s)
{
  int n = graph.size();
  int ans = 0;
  vector<int> ret(n, INT_MAX);

  for (int i = 0; i < n; i++) {
    for (auto x : graph[i]) {
      if (x.first != i)
        ret[x.first] = min(ret[x.first], x.second);
    }
  }

  for (int i = 0; i < n; i++) {
    if (i != s && ret[i] != INT_MAX) ans += ret[i];
    for (auto &x : graph[i]) {
      if (x.first == s || ret[x.first] == INT_MAX)continue;
      x.second -= ret[x.first];
    }
  }
  ret.clear();
  vector<int> cycle;
  memset(col, 0, sizeof col);

  bool found = false;
  for (int i = 0; i < n; i++) {
    if (!col[i] && findCycle(i, graph, cycle)) {
      found = true;
      break;
    }
  }

  if (!found) return ans;
  vector<bool> isCycle(n);
  for (auto i : cycle) isCycle[i] = 1;

  vector<vector<pii> > nEdge(n + 1);
  for (int i = 0; i < n; i++) {
    if (isCycle[i]) {
      for (auto x : graph[i]) {
        if (!isCycle[x.first])
          nEdge[n].push_back(x);
      }
    }
    else {
      for (auto x : graph[i]) {
        if (isCycle[x.first])
          x.first = n;
        nEdge[i].push_back(x);
      }
    }
  }
  graph.clear();
  cycle.clear();
  isCycle.clear();
  return ans + minCostArborescense(nEdge, s);
}


bool vis[N];
int dfs(int u, const vector<vector<pii> > &graph)
{
  vis[u] = 1;
  int ans = 1;
  for (auto x : graph[u]) {
    if (!vis[x.first])
      ans += dfs(x.first, graph);
  }
  return ans;
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
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    vector < vector <pii> > graph(n);
    for (int i = 0; i < m; i++) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      if (u == v || v == s)continue;
      graph[u].push_back({v, w});
    }
    memset(vis, 0, sizeof vis);
    if (dfs(s, graph) == n)
      printf("Case %d: %d\n", cs, minCostArborescense(graph, s));
    else printf("Case %d: impossible\n", cs);
  }
  return 0;
}
/****************************************************************************************************/
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

#define dbg1(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;
#define dbg4(w,x, y, z) cerr << #w << " = " << w << ", " <<#x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

const int N = 1005;
struct Edge {
    Edge() {}
    Edge(int _u, int _v, int _w) {u = _u, v = _v, w = _w;}
    int u, v, w;
};


int DMST(int n, vector<Edge> graph, int root)
{
    const int inf = 1e9;
    int ret = 0;
    while (true) {
        vector<int> cost(n, inf), Back(n), label(n, -1), bio(n, -1);
        for (auto x : graph) {
            if (x.u == x.v)continue;
            if (x.w < cost[x.v]) {
                cost[x.v] = x.w;
                Back[x.v] = x.u;
            }
        }

        cost[root] = 0;
        for (int i = 0; i < n; i++) {
            if (cost[i] == inf)return -1;
        }
        for (int i = 0; i < n; i++) ret += cost[i];
        int K = 0;

        for (int i = 0; i < n; i++) {
            int x = i;
            for (; x != root && bio[x] != i && label[x] < 0; x = Back[x])
                bio[x] = i;
            if (x != root && label[x] < 0) {
                for (; label[x] == -1; x = Back[x]) label[x] = K;
                ++K;
            }
        }
        if (K == 0) break;

        for (int i = 0; i < n; i++) {
            if (label[i] == -1) label[i] = K++;
        }

        for (int i = 0; i < (int)graph.size(); i++) {
            auto &x = graph[i];
            int p = label[x.u];
            int q = label[x.v];
            if (p != q) x.w -= cost[x.v];
            x.u = p;
            x.v = q;
        }
        root = label[root];
        n = K;
    }
    return ret;
}

int main()
{
    FASTIO
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
    vector<Edge> graph;
    for (int cs = 1; cs <= T; cs++) {
        int n, m, root;
        scanf("%d%d%d", &n, &m, &root);
        graph.clear();
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            graph.push_back(Edge(u, v, w));
        }
        int ans = DMST(n, graph, root);
        printf("Case %d: ", cs);
        if (ans == -1)puts("impossible");
        else printf("%d\n", ans);
        graph.clear();
    }
    return 0;
}
