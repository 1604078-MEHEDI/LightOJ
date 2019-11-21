///problem link: http://lightoj.com/volume_showproblem.php?problem=1017
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


const int N = 105;
int dp[N][N], v[N];
int n;
int k, w;
int calc(int pos, int k)
{
	if (pos >= n || k <= 0) return 0;
	int &ret = dp[pos][k];
	if (ret != -1) return ret;
	ret = 1;

	int idx = 0;
	for (idx = pos + 1; (idx < n && abs(v[pos] - v[idx]) <= w); idx++)
		ret++;

	ret += calc(idx, k - 1);
	ret = max(ret, calc(pos + 1, k));
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
	for (int cs = 1; cs <= T; cs++) {

		scanf("%d%d%d", &n, &w, &k);
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d %d", &x, &v[i]);
		}
		sort(v, v + n);
		memset(dp, -1, sizeof dp);
		printf("Case %d: %d\n", cs, calc(0, k));
	}
	return 0;
}
