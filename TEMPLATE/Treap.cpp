/*
 *	Problem	: TEMPLATE [SPOJ3273 ORDERSET]
 *	Author	: frank_c1
 *	Date	: 2015/12/17
 *	Tags	: Treap
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

#define LC ch[x][0]
#define RC ch[x][1]

const int maxn=200005;
int ch[maxn][2];
int rv[maxn],val[maxn],sz[maxn];
int idx=0,rt=0;

inline void newnode(int& x,int key) {
	x=++idx;
	LC=RC=0;rv[x]=rand();
	val[x]=key;sz[x]=1;
}

inline int dir(int x,int key) {
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

void ins(int& x,int key) {
	if(x==0) newnode(x,key);
	else {
		int d=dir(x,key);
		if(d==-1) return;
		ins(ch[x][d],key);
		if(rv[ch[x][d]]>rv[x]) rot(x,d^1);
	}
	pu(x);
}

void del(int& x,int key) {
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

inline bool find(int key) {
	for(int x=rt;x;) {
		int d=dir(x,key);
		if(d==-1) return true;
		x=ch[x][d];
	}
	return false;
}

inline int kth(int k) {
	int res=0;
	for(int x=rt;x;) {
		if(k==sz[LC]+1) res=val[x];
		if(k<sz[LC]+1) x=LC;
		else {k-=sz[LC]+1;x=RC;}
	}
	return res;
}

inline int rank(int key) {
	int res=0;
	for(int x=rt;x;) {
		if(key<=val[x]) x=LC;
		else {
			res+=sz[LC]+1;
			x=RC;
		}
	}
	return res;
}

inline void print(int x) {
	if(x) {
		print(LC);
		printf("%d ",val[x]);
		print(RC);
	}
}

int main() {
	int q,x,tot=0;
	char op[2];
	scanf("%d",&q);
	REP(i,1,q) {
		scanf("%s%d",op,&x);
		if(op[0]=='I' && !find(x)) {
			ins(rt,x);tot++;
		}
		else if(op[0]=='D' && find(x)) {
			del(rt,x);tot--;
		}
		else if(op[0]=='K') {
			if(x>tot || x<1) printf("invalid\n");
			else printf("%d\n",kth(x));
		}
		else if(op[0]=='C') 
			printf("%d\n",rank(x));
	}
	return 0;
}



