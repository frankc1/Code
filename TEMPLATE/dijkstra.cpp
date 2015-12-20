/*
 *	Problem	: TEMPLATE
 *	Author	: frank_c1
 *	Date	: 2015/12/16
 *	Tags	: 单源最短路径 dijkstra 
*/

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
#define REP(i,a,b) for(int i=(a);i<=(b);i++)
#define PER(i,a,b) for(int i=(a);i>=(b);i--)
#define RVC(i,S) for(int i=0;i<(S).size();i++)
#define RAL(i,u) for(int i=fr[u];i!=-1;i=e[i].next)
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

struct edge {
	int to,dist,next;
	edge(int x=0,int d=0):to(x),dist(d) {}
	bool operator < (const edge& b) const {return dist>b.dist;}
}; 
typedef edge node;

const int maxn=100005;
const int maxm=1000005;
const int INF=(int)(1e9);
edge e[maxm];
int fr[maxn],d[maxn];
int n,tote=0;

inline void addone(int u,int v,int d) {
	++tote;e[tote].next=fr[u];fr[u]=tote;
	e[tote].to=v;e[tote].dist=d;
}

inline void addedge(int u,int v,int d) {
	addone(u,v,d);addone(v,u,d);
}

priority_queue<node> Q;
void dijkstra(int s) {
	REP(i,1,n) d[i]=INF;
	d[s]=0;Q.push(node(s,d[s]));
	while(!Q.empty()) {
		node x=Q.top();Q.pop();
		int u=x.to;
		if(x.dist>d[u]) continue;
		RAL(i,u) 
			if(d[e[i].to]>d[u]+e[i].dist) {
				d[e[i].to]=d[u]+e[i].dist;
				Q.push(node(e[i].to,d[e[i].to]));
			}
	}
}

int main() {
	int m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	REP(i,1,n) fr[i]=-1;
	REP(i,1,m) {
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		addedge(u,v,d);
	}
	dijkstra(s);
	printf("%d\n",d[t]);
	return 0;	
}
