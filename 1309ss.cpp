
/// credit: mahbubul hasan shanto bhai
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



typedef pair<int, int> PII;
char line[200];
int id[200];

void process()
{
    stack<int> S;
    for (int i = 0; line[i]; i++) {
        id[i] = -1;
        if (line[i] == '(') S.push(i);
        else if (line[i] == ')') {
            int x = S.top();
            S.pop();
            id[i] = x;
            id[x] = i;
        }
    }
}

PII expression(int, int);

PII factor(int p, int q)
{
    if (line[p] == '(') return expression(p + 1, q - 1);
    if (line[p] == 'x') return PII(1, 0);
    int x = 0;
    for (int i = p; i <= q; i++) {
        if (line[i] >= '0' && line[i] <= '9')
            x = x * 10 + line[i] - '0';
    }
    return PII(0, x);
}

PII term(int p, int q)
{
    int i = p;
    while (i  < q) {
        if (line[i] == '*') {
            PII a = factor(p, i - 1);
            PII b = term(i + 1, q);
            return PII(a.first * b.second + b.first * a.second, b.second * a.second);
        }
        if (line[i] == '(') i = id[i];
        i++;
    }
    return factor(p, q);
}

PII expression(int p, int q)
{
    int i = q;
    while (i > p) {
        if (line[i] == '+') {
            PII a = expression(p, i - 1);
            PII b = term(i + 1, q);
            return PII(a.first + b.first, a.second + b.second);
        }
        else if (line[i] == '-') {
            PII a = expression(p, i - 1);
            PII b = term(i + 1, q);
            return PII(a.first - b.first, a.second - b.second);
        }
        if (line[i] == ')') i = id[i];
        i--;
    }
    return term(p, q);
}

PII equation(int p, int q)
{
    int i;
    for ( i = p; line[i] != '='; i++);
    PII a = expression(p, i - 1);
    PII b = expression(i + 1, q);
    return PII(a.first - b.first, a.second - b.second);
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
    for (int cs = 1; cs <= T; cs++) {
        scanf("%s", line);
        process();
        PII ans = equation(0, strlen(line) - 1);
        if (ans.first < 0) {
            ans.first *= -1;
            ans.second *= -1;
        }
        int g = __gcd(abs(ans.first), abs(ans.second));
        printf("Case %d: ", cs);
        if (ans.first == 0 && ans.second == 0) {
            printf("infinitely many solutions\n");
        }
        else if (ans.first == 0 && ans.second) {
            printf("no solution\n");
        }
        else if (abs(ans.second) % ans.first == 0)
            printf("%d\n", -ans.second / ans.first);
        else {
            printf("%d/%d\n", -ans.second / g, ans.first / g);
        }
    }
    return 0;
}
