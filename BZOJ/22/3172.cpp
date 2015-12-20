/**************************************************************
    Problem: 3172
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:1596 ms
    Memory:124408 kb
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
 
const int maxn=(int)(1e6)+5;
const int sigma_size=26;
vector<int> G[maxn];
queue<int> Q;
int ch[maxn][sigma_size];
int f[maxn];
int cnt[maxn],idx[205];
int siz;
 
int ord(char c) {return c-'a';}
int insert(char* s) {
    int u=0,n=strlen(s);
    for(int i=0;i<n;i++) {
        int c=ord(s[i]);
        if(!ch[u][c]) ch[u][c]=++siz;
        u=ch[u][c];
        cnt[u]++;
    }
    return u;
}
 
void getFail() {
    REP(i,0,siz) G[i].clear();
    f[0]=0;
    for(int c=0;c<sigma_size;c++) {
        int u=ch[0][c];
        if(!u) continue;
        f[u]=0;
        G[0].push_back(u);
        Q.push(u);
    }
    while(!Q.empty()) {
        int k=Q.front();Q.pop();
        for(int c=0;c<sigma_size;c++) {
            int u=ch[k][c];
            if(!u) continue;
            Q.push(u);
            int v=f[k];
            while(v && !ch[v][c]) v=f[v];
            f[u]=ch[v][c];
            G[f[u]].push_back(u);
        }
    }
}
 
void dfs(int u,int fa) {
    RVC(i,G[u]) {
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u);
        cnt[u]+=cnt[v];
    }
}
 
char buf[maxn];
int main() {
    siz=0;
    memset(ch,0,sizeof(ch));
    memset(cnt,0,sizeof(cnt));
    int n;
    read(n);
    REP(i,1,n) {
        scanf("%s",buf);
        idx[i]=insert(buf);
    }
    getFail();
    dfs(0,-1);
    REP(i,1,n) printf("%d\n",cnt[idx[i]]);
    return 0;
}
