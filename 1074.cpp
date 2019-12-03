#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int a[maxn];
int N,m;
int d[maxn];

struct Edge
{
    int source, dist, weight;
};
vector<Edge> graph;

void BellmanFord(int source)
{
     int E = graph.size();
    d[source] = 0;

    // vector<int>parent (N, -1);
    int u,v,w,k = N;

    // Relaxation step (run v-1 times)
    while(--k)
    {
        for(int j = 0; j < E; j++)
        {

            // edge from u to v having weight w
            u = graph[j].source;
            v = graph[j].dist;
            w = graph[j].weight;
          //  cout << u << " "<<v <<" "<< w<<endl;

            if(d[u] != INT_MAX && d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                //parent[v] = u;// set v's parent as u
            }
        }
    }
}

int main()
{
   // freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int T;
    cin >> T;
    for(int cs = 1; cs <= T; cs++)
    {
        graph.clear();
        cin >> N;
        for(int i = 1; i <= N; i++)cin >> a[i];
        for(int i = 1; i <= N; i++) d[i] = INT_MAX;
        cin >> m;
        for(int i = 0; i < m; i++)
        {
            int u,v;
            cin >> u >> v;
            int W = (a[v] - a[u]);
            int w = W*W*W;
            Edge input;
            input.source = u;
            input.dist = v;
            input.weight = w;
            graph.push_back(input);
        }
        BellmanFord(1);
        int q;
        cin >> q;
        cout << "Case "<<cs<<":\n";
        while(q--)
        {
            int x;
            cin >>x;
            if(d[x] == INT_MAX || d[x] < 3)cout << "?\n";
            else
            cout << d[x]<<endl;
        }
    }
}
