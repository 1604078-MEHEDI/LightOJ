///http://lightoj.com/volume_showproblem.php?problem=1154
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
const int inf = 1e9;
const int N = 210;

struct Edge
{
	int to, rev;
	int f, cap;
	Edge();
	Edge(int to, int rev, int f, int cap): to(to), rev(rev), f(f), cap(cap) {}
};

vector<Edge> graph[N];

void addEdge(int u, int v, int cap)
{
	Edge a = Edge(v, (int)graph[v].size(), 0, cap); // s to t
	Edge b = Edge(u, (int)graph[u].size(), 0, 0); // for directed grap capacity 0
	graph[u].push_back(a);
	graph[v].push_back(b);
}

int nodes, start[N], level[N];
queue<int> Q;

bool dinic_bfs(int s, int t)
{
	fill(level, level + nodes, -1);
	Q.push(s);
	level[s] = 0;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < (int)graph[u].size(); i++) {
			Edge &E = graph[u][i];
			int v = E.to;
			if (level[v] < 0 && E.f < E.cap) {
				Q.push(v);
				level[v] = level[u] + 1;
			}
		}
	}
	return level[t] >= 0;
}

int dinic_dfs(int u, int dst, int flow)
{
	if (u == dst) return flow;
	for (int &i = start[u]; i < (int)graph[u].size(); i++) {
		Edge &E = graph[u][i];
		int v = E.to;
		if (level[v] == level[u] + 1 && E.f < E.cap) {
			int cur_flow = dinic_dfs(v, dst, min(flow, E.cap - E.f));
			if (cur_flow > 0) {
				E.f += cur_flow;
				graph[v][E.rev].f -= cur_flow;
				return cur_flow;
			}
		}
	}
	return 0;
}

int dinic_flow(int s, int t)
{
	//dbg(s, t);
	int flow = 0;
	nodes = 210;
	while ((dinic_bfs(s, t))) {
		//dbg(flow);
		fill(start, start + nodes, 0);
		int delta;
		while ((delta = dinic_dfs(s, t, INT_MAX))) flow += delta;
	}
	return flow;
}

void init(int n)
{
	for (int i = 1; i <= n; i++)
		graph[i].clear();
}

struct Point
{
	double x, y;
	int now, cap;
};
Point a[N];


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
		double d;
		int penguins = 0;
		scanf("%d%lf", &n, &d);
		int s = 2 * n + 1;
		for (int i = 1; i <= n; i++) {
			double x, y, cap;
			int pg;
			scanf("%lf%lf%d%lf", &x, &y, &pg, &cap);
			//dbg(x, y, pg, cap);
			penguins += pg;
			a[i].x = x;
			a[i].y = y;
			a[i].now = pg;
			a[i].cap = cap;
		}
		bool got = false;
		nodes = N;
		printf("Case %d:", cs);
		for (int id = 1; id <= n; id++) {
			init(s);
			for (int i = 1; i <= n; i++) {
				addEdge(s, i, a[i].now);
				addEdge(i, n + i, a[i].cap);
			}

			for (int i = 1; i <= n; i++) {
				for (int j = i + 1; j <= n; j++) {
					double dd = (a[i].x - a[j].x) * (a[i].x - a[j].x)
					            + (a[i].y - a[j].y) * (a[i].y - a[j].y);
					dd = sqrt(dd);
					//dbg(dd, d);
					if (dd <= d) {
						addEdge(n + i, j, inf);
						addEdge(n + j, i, inf);
					}
				}
			}
			//dbg(s, id);
			int ans = dinic_flow(s, id);
			//dbg(ans);
			if (ans == penguins) {
				got = true;
				printf(" %d", id - 1);
			}
		}
		if (!got) printf(" -1");
		printf("\n");
		//printf("Case %d: %d\n", cs, ans);

	}
	return 0;
}
