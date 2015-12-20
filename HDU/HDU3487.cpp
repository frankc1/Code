/*
 *	Problem	: HDU3487
 *	Author	: frank_c1
 *	Date	: 2015/12/15
 *	Tags	: splay
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

#define LC ch[x][0]
#define RC ch[x][1]
#define SC ch[ch[rt][1]][0]

const int maxn=(6e5);
int fa[maxn],ch[maxn][2];
int sz[maxn],val[maxn],flip[maxn];
int rt,idx;
int n;
bool flag=false;

inline void newnode(int& x,int v,int p) {
	x=++idx;
	LC=RC=flip[x]=0;
	val[x]=v;fa[x]=p;sz[x]=1;
}

inline int dir(int x) {return ch[fa[x]][1]==x;}
inline void up(int x) {
	sz[x]=sz[LC] + sz[RC] + 1;
}
inline void down(int x) {
	if(flip[x]) {
		flip[LC]^=1;
		flip[RC]^=1;
		swap(LC,RC);
		flip[x]=0;
	}
}

inline void rot(int x) {
	int d=dir(x)^1,p=fa[x];
	down(p);down(x);
	ch[p][d^1]=ch[x][d];
	fa[ch[x][d]]=p;
	fa[x]=fa[p];
	if(fa[x]) ch[fa[p]][dir(p)]=x;
	ch[x][d]=p;fa[p]=x;up(p);
}

inline void splay(int x,int goal=0) {
	down(x);
	while(fa[x]!=goal) {
		down(fa[fa[x]]);
		down(fa[x]);down(x);
		if(fa[fa[x]]==goal) rot(x);
		else if(dir(x)!=dir(fa[x])) rot(x),rot(x);
		else rot(fa[x]),rot(x);
	}
	up(x);if(goal==0) rt=x;
}

inline void rto(int k,int goal=0) {
	int x=rt;
	down(x);
	for(;k!=sz[LC]+1;) {
		if(k<sz[LC]+1) x=LC;
		else {
			k-=sz[LC]+1;
			x=RC;
		}
		down(x);
	}
	splay(x,goal);
}

inline void build(int& x,int l,int r,int p) {
	if(l>r) return;
	int mid=(l+r)>>1;
	newnode(x,mid,p);
	build(LC,l,mid-1,x);
	build(RC,mid+1,r,x);
	up(x);
}

inline void init() {
	flag=false;
	rt=idx=0;
	newnode(rt,-1,0);
	newnode(ch[rt][1],-1,rt);
	sz[rt]=2;
	build(SC,1,n,ch[rt][1]);
}

inline void op_flip(int a,int b) {
	rto(a);rto(b+2,rt);
	flip[SC]^=1;
}

inline void op_cut(int a,int b,int c) {
	rto(a);rto(b+2,rt);
	int cp=SC;SC=0;
	up(ch[rt][1]);up(rt);
	rto(c+1);rto(c+2,rt);
	SC=cp;fa[cp]=ch[rt][1];
	up(ch[rt][1]);up(rt);
}

inline void print(int x) {
	if(x) {
		down(x);
		print(LC);
		if(val[x]!=-1) {
			if(flag) printf(" ");
			flag=true;
			printf("%d",val[x]);
		}
		print(RC);
	}
}

char op[10];
int main() {
	int m,a,b,c;
	while(true) {
		read(n);read(m);
		if(n==-1) break;
		init();
		REP(i,1,m) {
			scanf("%s",op);
			read(a);read(b);
			if(op[0]=='F') {
				op_flip(a,b);
			}
			if(op[0]=='C') {
				read(c);
				op_cut(a,b,c);
			}
		}
		print(rt);
		printf("\n");
	}
	return 0;
}






