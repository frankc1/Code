/**************************************************************
    Problem: 1041
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:100 ms
    Memory:1284 kb
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
 
LL gcd(LL a,LL b) {return b==0?a:gcd(b,a%b);}
 
int main() {
    LL r;
    read(r);
    int cnt=0;
    for(LL d=1;d*d<=2*r;d++) {
        if((2*r)%d!=0) continue;
        for(LL u=1;u*u<=2*r/d;u++) {
            LL v=(LL)sqrt(2*r/d-u*u);
            if(u>=v || u*u+v*v!=2*r/d) continue;
            if(gcd(u,v)==1) cnt++;
        }
        if(d*d==2*r) continue;
        for(LL u=1;u*u<=d;u++) {
            LL v=(LL)sqrt(d-u*u);
            if(u>=v || u*u+v*v!=d) continue;
            if(gcd(u,v)==1) cnt++;
        }
    }
    printf("%d\n",(cnt+1)*4);
    return 0;
}
