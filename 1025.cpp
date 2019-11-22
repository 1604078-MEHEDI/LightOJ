
////http://lightoj.com/volume_showproblem.php?problem=1025
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

char str[101];
ll dp[101][101];

ll solve(int l, int r)
{
  //dbg(l,r);
  if (l > r) return 0;
  if (l == r) return 1;

  ll &ret = dp[l][r];
  if (ret != -1) return ret;
  if (str[l] == str[r]) {
    return ret = (1 + solve(l + 1, r) + solve(l, r - 1));
  }
  else {
    return ret = solve(l + 1, r) + solve(l, r - 1) - solve(l + 1, r - 1);
  }

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
    scanf("%s", str);
    int n = strlen(str);
    //dbg(str);
    memset(dp, -1, sizeof dp);
    printf("Case %d: %lld\n", cs, solve(0, n - 1));
  }
  return 0;
}
