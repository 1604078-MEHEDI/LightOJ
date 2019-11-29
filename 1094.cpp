/// Topic: Tree Diameter
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

/**___________________________________________________**/

const int N = 30005;

const int inf = 1e9 + 7;
vector<pair<int, int> > graph[N];
vector<int> p, d;
void dijkstra(int s, int n)
{
	//dbg(s, n);
//    int n = graph.size();
	d.assign(n, inf);
	p.assign(n, -1);

	d[s] = 0;
	using pii = pair<int, int>;
	priority_queue<pii> PQ;

	PQ.push({0, s});

	while (!PQ.empty()) {
		int v = PQ.top().second;
		int d_v = PQ.top().first;
		PQ.pop();
		if (d_v != d[v]) continue;

		for (auto x : graph[v]) {
			int to = x.first;
			int len = x.second;

			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				PQ.push({d[to], to});
			}
		}
	}
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
	//dbg(T);
	for (int cs = 1; cs <= T; cs++) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i <= n; i++) graph[i].clear();
		//dbg(n);
		for (int i = 1; i  < n; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			//dbg(u, v, w);
			graph[u].push_back({v, w});
			graph[v].push_back({u, w});
		}

		dijkstra(0, n);
		int far = 0;
		int mx = 0;
		for (int i = 0; i < n; i++) {
			if (d[i] > mx) {
				mx = d[i];
				far = i;
			}
			//dbg(d[i], i);
		}
		//dbg(far);
		dijkstra(far, n);
		mx = 0;
		for (int i = 0; i < n; i++) {
			mx = max(mx, d[i]);
			//dbg(d[i], i);
		}

		printf("Case %d: %d\n", cs, mx);
	}
	return 0;
}
