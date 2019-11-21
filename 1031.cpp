/// problem link: http://lightoj.com/volume_showproblem.php?problem=1031
/// topic: dp
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


int dp[105][105];
int a[105];

int calc(int l, int r)
{
	if (l > r) return 0;
	int &ret = dp[l][r];
	if (ret != -1) return ret;

	int sm = 0;
	int dif = INT_MIN;
	for (int i = l; i <= r; i++) {
		sm += a[i];
		dif = max(dif, sm - calc(i + 1, r));
	}
	sm = 0;
	for (int i = r; i >= l; i--) {
		sm += a[i];
		dif = max(dif, sm - calc(l, i - 1));
	}
	return ret = dif;
}

int main()
{
	// FASTIO
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
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		memset(dp, -1, sizeof dp);
		printf("Case %d: %d\n", cs, calc(0, n - 1));
	}
	return 0;
}
/**------------------------------------------------------------------------------------------**/
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

///*
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
//*/
/**___________________________________________________**/

const int inf = 1e9 + 7;
int n, a[105], dp[105][105][2], s[105][105];

int solve(int l, int r, int turn)
{
  if (l + r == n) return 0;
  int &ret = dp[l][r][turn];
  if (ret != inf) return ret;
  if (turn) ret = inf;
  else ret = -inf;

  for (int i = 1; i <= n - l - r; i++) {
    //take from the left
    if (turn) ret = min(ret, -s[l + 1][l + i] + solve(l + i, r, 1 - turn));
    else ret = max(ret, s[l + 1][l + i] + solve(l + i, r, 1 - turn));


    if (turn) ret = min(ret, -s[n - r - i + 1][n - r] + solve(l, r + i, 1 - turn));

    else ret = max(ret, s[n - r - i + 1][n - r] + solve(l, r + i, 1 - turn));
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
  for (int cs = 1; cs <= T; cs++) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) s[i][j] = 0;
    }

    for (int l = 1; l <= n; l++) {
      for (int r = l; r <= n; r++) {
        s[l][r] = s[l][r - 1] + a[r];
      }
    }

    // for (int l = 1; l <= n; l++) {
    //   cerr << setw(l*2);
    //   for (int r = l; r <= n; r++) {
    //     //s[l][r] = s[l][r - 1] + a[r];
    //     cerr << s[l][r] << " ";
    //   }
    //   cerr << endl;
    // }

    for (int l = 0; l <= n; l++)
      for (int r = 0; r <= n; r++)
        for (int f = 0; f <= 1; f++)dp[l][r][f] = inf;

    printf("Case %d: %d\n", cs, solve(0, 0, 0));
  }
  return 0;
}
