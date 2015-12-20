/**************************************************************
    Problem: 1007
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:248 ms
    Memory:2448 kb
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
 
const double eps=1e-8;
struct line {
    double a,b;
};
 
const int maxn=50005;
line ls[maxn]; 
int rk[maxn],stk[maxn];
int top=0;
 
bool cmp(int i,int j) {
    if(fabs(ls[i].a-ls[j].a)<eps) 
        return ls[i].b<ls[j].b;
    else return ls[i].a<ls[j].a;
}
 
double GetCross(line x,line y) {
    return (y.b-x.b)/(x.a-y.a);
}
 
 
int main() {
    int n;
    scanf("%d",&n);
    REP(i,1,n) rk[i]=i;
    REP(i,1,n) scanf("%lf%lf",&ls[i].a,&ls[i].b);
    sort(rk+1,rk+n+1,cmp);
    REP(i,1,n) {
        int k=rk[i];
        line nw=ls[k];
        while(top) {
            if((nw.a-ls[stk[top]].a)<eps) top--;
            else if(top>1 && GetCross(nw,ls[stk[top]])-GetCross(ls[stk[top]],ls[stk[top-1]])<eps) top--;
            else break;
        }
        stk[++top]=k;
    }
    sort(stk+1,stk+top+1);
    REP(i,1,top) printf("%d ",stk[i]);
    return 0;
}
