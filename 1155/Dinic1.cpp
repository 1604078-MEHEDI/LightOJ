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

*//**___________________________________________________**/

const int inf = 1e9;
const int N = 100001;

struct DinicMaxflow
{
	struct Edge
	{
		int a, b, cap, flow;
		Edge(int _a, int _b, int _c, int _d)
		{
			a = _a;
			b = _b;
			cap = _c;
			flow = _d;
		}
	};

	int n, s, t, level[N], parent[N];
	vector<Edge> E;
	vector<int> graph[N];
	queue<int> Q;

	void add_edge(int a, int b, int cap)
	{
		Edge e1 = Edge(a, b, cap, 0);
		Edge e2 = Edge(b, a, 0, 0);// edge capacity will be cap for bidirectional edge
		//if multiple edge occurs all edge should be sonsidered
		graph[a].push_back((int)E.size());
		E.push_back(e1);
		graph[b].push_back((int)E.size());
		E.push_back(e2);
	}

	bool bfs()
	{
		memset(level, -1, sizeof level);
		level[s] = 0;
		Q.push(s);

		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for (auto id : graph[u]) {
				int v = E[id].b;
				if (level[v] == -1 && E[id].flow < E[id].cap) {
					level[v] = level[u] + 1;
					Q.push(v);
				}
			}
		}
		return level[t] != -1;
	}

	int dfs(int u, int flow) {
		if (!flow) return 0;
		if (u == t) return flow;
		for (; parent[u] < (int)graph[u].size(); ++parent[u]) {
			int id = graph[u][parent[u]];
			int v = E[id].b;
			if (level[v] != level[u] + 1) continue;
			int mxflow = dfs(v, min(flow, E[id].cap - E[id].flow));
			if (mxflow) {
				E[id].flow += mxflow;
				E[id ^ 1].flow -= mxflow;
				return mxflow;
			}
		}
		return 0;
	}

	int MaxFlow()
	{
		int flow = 0;
		while (bfs()) {
			//dbg(flow);
			memset(parent, 0, sizeof parent);
			int mxflow;
			while ((mxflow = dfs(s, inf))) {
				flow += mxflow;
			//dbg(flow);
				if (mxflow == 0) break;
			}
		}
		return flow;
	}

	void init(int _n, int _s, int _t)
	{
		n = _n;
		s = _s;
		t = _t;
		for (int i = 0; i < (int)E.size(); i++) E[i].flow = 0;
	}

	void RESET() {
		E.clear();
		for (int i = 0; i <= n; i++) graph[i].clear();
	}
} DMF;


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
	//dbg(T);
	//T = 1;
	for (int cs = 1; cs <= T; cs++) {
		int n;
		scanf("%d", &n);
		//dbg(n);
		DMF.RESET();
		DMF.init(2 * n + 2, 0, 2 * n + 1);
		for (int i = 1; i <= n; i++) {
			int cap;
			scanf("%d", &cap);
			DMF.add_edge(i, i + n, cap);
		}
		int m;
		scanf("%d", &m);
		//dbg(m);
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			DMF.add_edge(u + n, v, w);
		}
		int B, D;
		scanf("%d %d", &B, &D);
		for (int i = 1; i <= B; i++) {
			int x;
			scanf("%d", &x);
			DMF.add_edge(0, x, inf);
		}
		//dbg(B,D);
		for (int i = 1; i <= D; i++) {
			int x;
			scanf("%d", &x);
			DMF.add_edge(x + n, 2 * n + 1, inf);
		}
		//dbg(B,D);
		int ans = DMF.MaxFlow();
		//dbg(B,D);
		printf("Case %d: %d\n", cs, ans);
	}
	return 0;
}
