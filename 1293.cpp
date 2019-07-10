#include <bits/stdc++.h>
using namespace std;
#define INF 500000000
#define endl '\n'
#define maxn 50005
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
typedef long long ll;
const double PI = acos(-1.0);
#define dbg(x) cerr << #x << " = " << x << endl;
#define dbg2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;
#define dbg3(x, y, z) cerr << #x << " = " << x << ", " << #y << " = " << y << ", " << #z << " = " << z << endl;

int  a[maxn]; // word position
int l, r, b[maxn];
int m; // word length
int n; // koyta word ase
map<string, int> mp;


/*
- word gula alada kora
- uniqe word numburing kora
- number gular position ekta array te rakha
- jokhn m ta value pabo tokhn range check korbo
- evabe minimum range ta nibo
*/
int getIdx(const string &s)
{
	int i = mp[s];
	if (!i) i = mp[s] = ++m;
	return i;
}

void Input()
{
	char s[111];
	mp.clear();
	n = m = 0;
	while (scanf("%s ", s)) {
		//cerr << s << endl;
		if (strcmp(s, "END") == 0) break;
		int len = strlen(s);
		for (int i = 0; i < len;) {
			if (isalpha(s[i])) {
				string t = "";
				while (i < len && isalpha(s[i]))
					t += s[i++];// word alada kortesi
				//cerr << t << endl;
				a[++n] = getIdx(t);
				//cerr << a[n] << " " << n << " " << m <<  " " << t << endl;
			}
			else i++;
		}
	}
}

void solve()
{
	for (int i = 1; i <= m; i++) b[i] = 0;
	l = 0, r = INF;
	int cnt = 0;

	for (int f = 1, i = 1; f <= n; f++) {
		if (++b[a[f]] == 1)cnt++;
		while (i < f && b[a[i]] > 1){
			b[a[i++]]--;
			//cerr << b[a[i]] << " "<<i << " "<<a[i] << endl;
		}

		if (cnt == m && f - i < r - l) {
			l = i;
			r = f;
			//cerr << l << " "<<r <<" "<< (r - l + 1) << endl;
		}
	}

}

int main()
{
	//FASTIO
	///*
	//double start_time = clock();
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#endif
//*/
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		Input();
		solve();
		printf("Case %d: %d %d\n", cs, l, r);
		//cerr << "---------------------------------\n";
	}

	//double end_time = clock();
	//printf( "Time = %lf ms\n", ( (end_time - start_time) / CLOCKS_PER_SEC)*1000);
	return 0;
}



