/**************************************************************
    Problem: 1053
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:92 ms
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
 
LL n,ans=0,mxp=0;
int pr[]={2,3,5,7,11,13,17,19,23,29,31};
int ed=11;
 
void dfs(int cur,LL nw,LL cnt) {
    if(cur==ed) {
        if(cnt>mxp) {ans=nw;mxp=cnt;}
        else if(nw<ans && cnt>=mxp) {ans=nw;mxp=cnt;}
        return;
    }
    LL num=1;
    for(int i=0;;i++) {
        if(nw*num>n) break;
        dfs(cur+1,nw*num,cnt*(i+1));
        num*=pr[cur];
    }
}
int main() {
    read(n);
    dfs(0,1,1);
    printf("%lld\n",ans);
    return 0;   
}
