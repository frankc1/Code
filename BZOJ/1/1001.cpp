/**************************************************************
    Problem: 1001
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:2328 ms
    Memory:118596 kb
****************************************************************/

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
    int to,next;
    LL dist;
    edge(int x=0,LL d=0):to(x),dist(d) {}
    bool operator < (const edge& b) const {return dist>b.dist;}
}; 
typedef edge node;
 
const int maxn=(int)(2e6)+5;
const int maxm=(int)(6e6)+5;
const LL INF=(LL)(1e18);
edge e[maxm];
int fr[maxn];
LL d[maxn];
int nn,tote=0;
 
inline void addone(int u,int v,LL d) {
    ++tote;e[tote].next=fr[u];fr[u]=tote;
    e[tote].to=v;e[tote].dist=d;
}
 
inline void addedge(int u,int v,int d) {
    addone(u,v,d);addone(v,u,d);
}
 
priority_queue<node> Q;
void dijkstra(int s) {
    REP(i,0,nn-1) d[i]=INF;
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
 
void solve() {
    int n,m,x,y;
    LL dst;
    read(n);read(m);
    nn=(n-1)*(m-1)*2+2;
    REP(i,0,nn-1) fr[i]=-1;
    REP(i,1,n) REP(j,1,m-1) {
        read(dst);
        x=((i-2)*(m-1)+j-1)<<1|1;
        y=((i-1)*(m-1)+j-1)<<1;
        if(i==1) x=nn-2;
        if(i==n) y=nn-1;
        addedge(x,y,dst);
    }
    REP(i,1,n-1) REP(j,1,m) {
        read(dst);
        x=((i-1)*(m-1)+j-1)<<1|1;
        y=((i-1)*(m-1)+j-2)<<1;
        if(j==1) y=nn-1;
        if(j==m) x=nn-2;
        addedge(x,y,dst);
    }
    REP(i,1,n-1) REP(j,1,m-1) {
        read(dst);
        x=((i-1)*(m-1)+j-1)<<1;
        y=((i-1)*(m-1)+j-1)<<1|1;
        addedge(x,y,dst);
    }
    dijkstra(nn-2);
    printf("%lld\n",d[nn-1]);
}
 
int main() {
    solve();
    return 0;
}
