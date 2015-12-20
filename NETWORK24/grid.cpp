#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cctype>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x)&(-x)
#define REP(i,a,b) for(int i=(a);i<=(b);i++)
#define PER(i,a,b) for(int i=(a);i>=(b);i--)
#define RVC(i,S) for(int i=0;i<(S).size();i++)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

template<class T> inline
void read(T& num) {
	bool start=false,neg=false;
	char c;
	num=0;
	while((c=getchar())!=EOF) {
		if(c=='-') start=neg=true;
		else if(c>='0' && c<='9') {
			start=true;
			num=num*10+c-'0';
		} else if(start) break;
	}
	if(neg) num=-num;
}
/*============ Header Template ============*/

struct Edge {
	int from,to,cap,flow;
};

int s,t;
const int maxn=500+5;
const int INF=(int)(1e9);
vector<Edge> edges;
vector<int> G[maxn];
int d[maxn],cur[maxn];
bool vis[maxn];

void AddEdge(int from,int to,int cap) {
	edges.push_back((Edge){from,to,cap,0});
	edges.push_back((Edge){to,from,0,0});
	int m=edges.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
}

queue<int> Q;
bool bfs() {
	memset(cur,0,sizeof(cur));
	memset(vis,0,sizeof(vis));
	d[s]=0;vis[s]=1;
	Q.push(s);
	while(!Q.empty()) {
		int u=Q.front();Q.pop();
		RVC(i,G[u]) {
			Edge& e=edges[G[u][i]];
			if(!vis[e.to] && e.cap > e.flow) {
				d[e.to]=d[u]+1;
				vis[e.to]=1;
				Q.push(e.to);
			}
		}
	}
	return vis[t];
}

int dfs(int u,int a) {
	if(u==t || a==0) return a;
	int flow=0,f;
	for(int& i=cur[u]; i<G[u].size(); i++) {
		Edge& e=edges[G[u][i]];
		if(d[e.to]==d[u]+1 && (f=dfs(e.to,min(a,e.cap-e.flow)))>0) {
			e.flow+=f;
			edges[G[u][i]^1].flow-=f;
			flow+=f;
			a-=f;
			if(!a) break;
		}
	}
	return flow;
}

int Maxflow() {
	int flow=0;
	while(bfs()) flow+=dfs(s,INF);
	return flow;
}

int n,m;
int mp[maxn][maxn];
int dx[]= {-1,0,1,0};
int dy[]= {0,1,0,-1};

bool in_law(int x,int y) {
	if(x>=1 && x<=n && y>=1 && y<=m) return true;
	else return false;
}

int main() {
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int a,idx=2,tot=0;
	s=1;t=2;
	scanf("%d%d",&n,&m);
	REP(i,1,n) REP(j,1,m) {
		scanf("%d",&a);
		tot+=a;
		mp[i][j]=++idx;
		if((i+j)&1) AddEdge(s,idx,a);
		else AddEdge(idx,t,a);
	}
	REP(i,1,n) REP(j,1,m) if((i+j)&1)
		REP(k,0,3) {
		int ni=i+dx[k],nj=j+dy[k];
		if(in_law(ni,nj)) AddEdge(mp[i][j],mp[ni][nj],INF);
	}
	printf("%d\n",tot-Maxflow());
	return 0;
}
