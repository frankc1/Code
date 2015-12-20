/**************************************************************
    Problem: 3673
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:60 ms
    Memory:5120 kb
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
 
const int maxn=(int)(2e4)+100;
int rt[maxn],ls[maxn<<4],rs[maxn<<4],fa[maxn<<4];
int idx=0,nw=0;
int n;
void build(int l,int r,int& x) {
    x=++idx;
    ls[x]=rs[x]=0;
    if(l==r) {
        fa[x]=r;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,ls[x]);
    build(mid+1,r,rs[x]);
}
 
void upd(int l,int r,int& x,int last,int p,int val) {
    x=++idx;
    ls[x]=ls[last];rs[x]=rs[last];
    if(l==r) {fa[x]=val;return;}    
    int mid=(l+r)>>1;
    if(p<=mid) upd(l,mid,ls[x],ls[last],p,val);
    else upd(mid+1,r,rs[x],rs[last],p,val);
}
 
int getx(int l,int r,int x,int p) {
    if(l==r) return fa[x];
    int mid=(l+r)>>1;
    if(p<=mid) return getx(l,mid,ls[x],p);
    else return getx(mid+1,r,rs[x],p); 
}
 
inline int f(int x) {return getx(1,n,rt[nw],x);}
 
int Find(int x) {return f(x)==x?x:Find(f(x));}
 
int main() {
    int m,op,a,b;
    read(n);read(m);
    build(1,n,rt[0]);
    REP(i,1,m) {
        read(op);read(a);
        if(op==1) {
            read(b);
            int x=Find(a),y=Find(b);
            ++nw;
            upd(1,n,rt[nw],rt[nw-1],x,y); 
        }
        if(op==2) {
            ++nw;
            rt[nw]=rt[a];
        }
        if(op==3) {
            read(b);
            ++nw;
            rt[nw]=rt[nw-1];
            int x=Find(a),y=Find(b);
            if(x==y) printf("1\n");
            else printf("0\n");
        }
    }
    return 0;
}
