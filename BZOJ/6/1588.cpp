/**************************************************************
    Problem: 1588
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:236 ms
    Memory:48152 kb
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
 
#define LC ch[x][0]
#define RC ch[x][1]
 
const int maxn=2000005;
const LL INF=(LL)(1e15);
int ch[maxn][2];
int rv[maxn],sz[maxn];
LL val[maxn];
int idx=0,rt=0;
 
inline void newnode(int& x,LL key) {
    x=++idx;
    LC=RC=0;rv[x]=rand();
    val[x]=key;sz[x]=1;
}
 
inline int dir(int x,LL key) {
    if(val[x]==key) return -1;
    else return key>val[x];  
}
 
inline void pu(int x) {
    sz[x]=sz[LC] + sz[RC] +1;
}
 
inline void rot(int& x,int d) {
    int k=ch[x][d^1];
    ch[x][d^1]=ch[k][d];
    ch[k][d]=x;
    pu(x);pu(k);x=k;
}
 
void ins(int& x,LL key) {
    if(x==0) newnode(x,key);
    else {
        int d=dir(x,key);
        if(d==-1) return;
        ins(ch[x][d],key);
        if(rv[ch[x][d]]>rv[x]) rot(x,d^1);
    }
    pu(x);
}
 
void del(int& x,LL key) {
    int d=dir(x,key);
    if(d==-1) {
        if(!LC) x=RC;
        else if(!RC) x=LC;
        else {
            int dk=(rv[LC]>rv[RC]);
            rot(x,dk);del(ch[x][dk],key);
        }
    }
    else del(ch[x][d],key);
    if(x) pu(x);
}
 
LL pre(int x,LL key) {
    if(!x) return -INF;
    if(key<val[x]) return pre(LC,key);
    else if(key==val[x]) return key;
    else return max(val[x],pre(RC,key));
}
 
LL nxt(int x,LL key) {
    if(!x) return INF;
    if(key<val[x]) return min(val[x],nxt(LC,key));
    else if(key==val[x]) return key;
    else return nxt(RC,key);
}
 
int main() {
    int n;
    LL key;
    LL ans=0;
    read(n);
    REP(i,1,n) {
        read(key);
        if(i==1) ans+=key;
        else {
            LL x=pre(rt,key),y=nxt(rt,key);
            ans+=min(key-x,y-key);
        }
        ins(rt,key);    
    }
    printf("%lld\n",ans);
    return 0;
}
