/*
 *	Problem	: TEMPLATE
 *	Author	: frank_c1
 *	Date	: 2015/12/16
 *	Tags	: FFT
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

struct cpx {
	double x,y;
	cpx(double a=0,double b=0):x(a),y(b) {}
};

cpx operator + (cpx a,cpx b) {return cpx(a.x+b.x,a.y+b.y);}
cpx operator - (cpx a,cpx b) {return cpx(a.x-b.x,a.y-b.y);}
cpx operator * (cpx a,cpx b) {return cpx(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}

const int maxn=(int)(4e5)+5;
const double pi=acos(-1.0);
cpx A[maxn],B[maxn];

void DFT(cpx* a,int n,int d=1) {
	for(int i=(n>>1),j=1;j<n;j++) {
		if(i<j) swap(a[i],a[j]);
		int k;for(k=(n>>1);i&k;i^=k,k>>=1);
		i^=k;
	}
	for(int m=2;m<=n;m<<=1) {
		cpx w=cpx(cos(pi*2/m*d),sin(pi*2/m*d));
		for(int i=0;i<n;i+=m) {
			cpx s=cpx(1,0);
			for(int j=i;j<(i+(m>>1));j++) {
				cpx u=a[j],v=s*a[j+(m>>1)];
				a[j]=u+v;a[j+(m>>1)]=u-v;
				s=s*w;
			}	
		}
	}
	if(d==-1) for(int i=0;i<n;i++) a[i].x=a[i].x/n;
}

int main() {
	int n,m,len=0;
	read(n);read(m);
	for(int i=0;i<n;i++) read(A[i].x);
	for(int i=0;i<m;i++) read(B[i].x);
	while((1<<len) < (max(n,m)<<1)) len++;
	DFT(A,1<<len);DFT(B,1<<len);
	for(int i=0;i<(1<<len);i++) A[i]=A[i]*B[i];
	DFT(A,1<<len,-1);
	for(int i=0;i<n+m-1;i++) printf("%d ",(int)trunc(A[i].x+0.5));
	return 0;
}
