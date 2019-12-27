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
const int N = 205;
int n;
int capacity[N][N];
int deg[N];
int graph[N][N];
int q[N];

int dinic(int n, int s, int t)
{
	//dbg(n, s, t);
	int par[2 * N], u, v, i, z, flow = 0, qh, qt, inc;

	while (1) {
		memset(par, -1, sizeof par);
		qh = qt = 0;
		par[s] = -2;
		q[qt++] = s;
		while (qt != qh && par[t] == -1) {
			u = q[qh++];
			for (i = 0; i < deg[u]; i++) {
				v = graph[u][i];
				if (par[v] == -1 && capacity[u][v]) {
					par[v] = u;
					q[qt++] = v;
				}
			}
		}
		if (par[t] == -1) break;
		for (z = 0; z < n; z++)if (par[z] != -1 && capacity[z][t]) {
				inc = capacity[z][t];
				for (v = z, u = par[v]; u >= 0; v = u, u = par[v])
					inc = min(inc, capacity[u][v]);
				if (!inc) continue;
				capacity[z][t] -= inc;
				capacity[t][z] += inc;
				for (v = z, u = par[v]; u >= 0; v = u, u = par[v]) {
					capacity[u][v] -= inc;
					capacity[v][u] += inc;
				}
				flow += inc;
			}
	}
	return flow;
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
		memset(capacity, 0, sizeof capacity);
		for (int i = 1; i <= n; i++) scanf("%d", &capacity[i][i + n]);
		int m, k, s = 0, t = 2 * n + 1;
		scanf("%d", &m);
		while (m--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			capacity[u + n][v] += w;
		}
		int B, D;
		scanf("%d %d", &B, &D);
		while (B--) {
			scanf("%d", &k);
			capacity[s][k] = inf;
		}
		while (D--) {
			scanf("%d", &k);
			capacity[k + n][t] = inf;
		}
		memset(deg, 0, sizeof deg);
		for (int i = s; i <= t; i++)
			for (int j = s; j <= t; j++)
				if (capacity[i][j] || capacity[j][i])
					graph[i][deg[i]++] = j;
		printf("Case %d: %d\n", cs, dinic(t + 1, s, t));
	}
	return 0;
}
