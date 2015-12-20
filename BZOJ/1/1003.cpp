/**************************************************************
    Problem: 1003
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:56 ms
    Memory:1380 kb
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
 
const int maxn=25;
const int maxd=105;
const int maxm=805;
const LL INF=(LL)(1e15);
edge e[maxm];
int fr[maxn];
bool inq[maxn];
bool ok[maxn][maxd];
int cnt[maxn];
LL d[maxn];
LL cost[maxd][maxd];
LL f[maxd];
int n,ds,st,ed,tote=0;
 
inline void addone(int u,int v,int d) {
    ++tote;e[tote].next=fr[u];fr[u]=tote;
    e[tote].to=v;e[tote].dist=d;
}
 
inline void addedge(int u,int v,int d) {
    addone(u,v,d);addone(v,u,d);
}
 
bool in_law(int u) {
    REP(i,st,ed) if(!ok[u][i]) return false;
    return true;
}
 
queue<int> Q; 
bool SPFA(int s) {
    REP(i,1,n) d[i]=INF;
    memset(cnt,0,sizeof(cnt));
    memset(inq,0,sizeof(inq));
    d[s]=0;inq[s]=1;Q.push(s);
    while(!Q.empty()) {
        int u=Q.front();
        Q.pop();inq[u]=0;
        RAL(i,u) 
            if(in_law(e[i].to) && d[e[i].to]>d[u]+e[i].dist) {
                d[e[i].to]=d[u]+e[i].dist;
                if(!inq[e[i].to]) {
                    inq[e[i].to]=1;
                    Q.push(e[i].to);
                    if(++cnt[e[i].to]>n) return false;
                }
            }
    }
    return true;
}
 
void solve() {
    int k,ne,q;
    read(ds);read(n);
    read(k);read(ne);
    REP(i,1,n) fr[i]=-1;
    REP(i,1,ne) {
        int u,v;LL d;
        read(u);read(v);read(d);
        addedge(u,v,d);
    }
    REP(i,1,n) REP(j,1,ds)
        ok[i][j]=true;
    read(q);
    REP(i,1,q) {
        int p,a,b;
        read(p);read(a);read(b);
        REP(j,a,b) ok[p][j]=false;
    }
    for(st=1;st<=ds;st++) 
        for(ed=st;ed<=ds;ed++) {
            SPFA(1);
            cost[st][ed]=d[n]*(ed-st+1);
        }
    REP(i,1,ds) f[i]=INF;
    f[0]=-k;
    REP(i,1,ds) REP(j,0,i-1) 
        f[i]=min(f[i],f[j]+cost[j+1][i]+k);
    printf("%lld\n",f[ds]);
}
 
int main() {
    solve();
    return 0;
}
