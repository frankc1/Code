/**************************************************************
    Problem: 1008
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:1272 kb
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
 
LL pow_mod(LL b,LL p,LL k) {
    LL res=1;
    for(;p;p>>=1) {
        if(p&1) res=(res*b)%k;
        b=(b*b)%k;
    }
    return res;
}
 
const LL mo=100003;
int main() {
    LL n,m;
    read(m);read(n);
    LL ans=pow_mod(m,n,mo)-pow_mod(m-1,n-1,mo)*m;
    if(ans<0) ans=mo-(-ans)%mo;
    else ans=ans%mo;
    printf("%lld\n",ans);
    return 0;
} 
