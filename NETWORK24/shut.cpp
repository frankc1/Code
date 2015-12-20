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
#include <complex>
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

string L;
int id;
bool End;
inline void ReadLine() {
	getline(cin,L);
	id=0;
	End=false;
}

template<class T> inline
bool read(T& num) {
	bool start=false,neg=false;
	char c;
	num=0;
	for(int& i=id; i<L.length(); i++) {
		c=L[i];
		if(c=='-') start=neg=true;
		else if(c>='0' && c<='9') {
			start=true;
			num=num*10+c-'0';
		} else if(start) break;
	}
	if(neg) num=-num;
	if(id>=L.length()) End=true;
	return start;
}
/*============ Header Template ============*/

struct Edge {
	int from,to,cap,flow;
};

int s,t;
const int maxn=1000+5;
const int INF=(int)(1e9);
vector<Edge> edges;
vector<int> G[maxn];
int d[maxn],cur[maxn];
bool vis[maxn];
queue<int> Q;

void AddEdge(int from,int to,int cap) {
	edges.push_back((Edge){from,to,cap,0});
	edges.push_back((Edge){to,from,0,0});
	int m=edges.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
}

bool bfs() {
	memset(cur,0,sizeof(cur));
	memset(vis,0,sizeof(vis));
	d[s]=0;vis[s]=1;
	Q.push(s);
	while(!Q.empty()) {
		int u=Q.front();Q.pop();
		RVC(i,G[u]) {
			Edge& e=edges[G[u][i]];
			if(!vis[e.to] && e.cap>e.flow) {
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

int idxa[maxn],idxb[maxn];
bool ans[maxn];
int main() {
	freopen("shut.in","r",stdin);
	freopen("shut.out","w",stdout);
	string S;
	int m,n,a,u,v,siz=2,tot=0;
	s=1;t=2;
	ReadLine();
	read(m);read(n);
	REP(i,1,m) {
		u=idxa[i]=++siz;
		ReadLine();
		read(a);
		tot+=a;
		if(a) AddEdge(s,u,a);
		while(!End) {
			read(v);
			if(!idxb[v]) idxb[v]=++siz;
			AddEdge(u,idxb[v],INF);
			if(End) break;
		}
	}
	ReadLine();
	REP(i,1,n) {
		read(a);
		if(a) AddEdge(idxb[i],t,a);
	}
	int k=Maxflow();
	REP(i,1,m) if(vis[idxa[i]]) printf("%d ",i);
	printf("\n");
	REP(i,1,n) if(vis[idxb[i]]) printf("%d ",i);
	printf("\n%d\n",tot-k);
	return 0;
}
