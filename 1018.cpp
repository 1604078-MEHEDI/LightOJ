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

const int N = 16;
struct node
{
	int x, y;
} p[N];
vector < int > G[70000];
int dp[1 << N], line[N][N];
void init()
{
	for (int i = 0; i < (1 << N); i++) {
		for (int j = 0; j < N; j++) {
			if (!(i & (1 << j)))
				G[i].push_back(j);
		}
	}
}

bool co_linear(int i, int j, int k)
{
	return ( (p[i].x - p[j].x) * (p[i].y - p[k].y) == (p[i].y - p[j].y) * (p[i].x - p[k].x));
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
	init();
	scanf("%d", &T);
	//T = 1;
	for (int cs = 1; cs <= T; cs++) {
		int n;
		scanf("%d", &n);
		memset(dp, 127, sizeof dp);
		memset(line, 0, sizeof line);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &p[i].x, &p[i].y);
			line[i][i] = (1 << i);
		}

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				for (int k = 0; k < n; k++) {
					if (!co_linear(i, j, k))continue;
					line[i][j] |= 1 << k;
				}

		int tot = (1 << n) - 1;
		dp[0] = 0;
		for (int i = 0; i < tot; i++) {
			int x = G[i][0];
			for (auto y : G[i]) {
				dp[i | line[x][y]] = min(dp[i | line[x][y]], dp[i] + 1);
			}
		}
		printf("Case %d: %d\n", cs, dp[tot]);
	}
	return 0;
}
//*************************************************************************************************************************************************
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

const int N = 16;
int n;
int x[N], y[N];
int col[N][N];
int dp[1 << N];
int point[1 << N];

int solve(int mask)
{
  if (mask == 0) return 0;
  int &ret = dp[mask];
  if (ret != -1) return ret;
  int t = mask;
  vector<int> vec;
  while (t) {
    int x = t & -t;
    vec.push_back(point[x]);
    t -= x;
  }
  ret = INT_MAX;
  if ((int)vec.size() == 1) return ret = 1;
  int pivot = vec[0];
  for (int i = 1; i < (int)vec.size(); i++) {
    ret = min(ret, 1 + solve(mask & col[pivot][vec[i]]));
  }
  return ret;
}

int main()
{
//  FASTIO
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
  for (int i = 0; i < N; i++) {
    point[1 << i] = i;
    //dbg(point[1 << i], 1 << i);
  }
  for (int cs = 1; cs <= T; cs++) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &x[i], &y[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        col[i][j] = (1 << n) - 1;
        for (int k = 0; k < n; k++) {
          if ((x[i] - x[j]) * (y[i] - y[k]) == (y[i] - y[j]) * (x[i] - x[k]))
            col[i][j] = col[i][j] & (~(1 << k));
        }
        col[j][i] = col[i][j];
      }
    }
    memset(dp, -1, sizeof dp);
    int ans = solve((1 << n) - 1);
    printf("Case %d: %d\n", cs, ans);
  }
  return 0;
}
