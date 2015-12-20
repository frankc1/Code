/**************************************************************
    Problem: 1009
    User: frank_c1
    Language: C++
    Result: Accepted
    Time:60 ms
    Memory:1276 kb
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
 
const int maxn=25;
int mo;
 
struct Matrix {
    int r,c;
    LL mat[maxn][maxn];
    Matrix(int x=0,int y=0):r(x),c(y) {memset(mat,0,sizeof(mat));}
};
 
Matrix operator * (Matrix a,Matrix b) {
    Matrix c(a.r,b.c);
    REP(k,0,a.c-1)
        REP(i,0,a.r-1) if(a.mat[i][k]>0)
            REP(j,0,b.c-1) if(b.mat[k][j]>0)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mo;
    return c;
}
 
Matrix MatPow(Matrix a,LL p) {
    Matrix c(a.r,a.r);
    REP(i,0,a.r-1) REP(j,0,a.r-1) c.mat[i][j]=(i==j);
    for(;p;p>>=1) {
        if(p & 1) c=c*a;
        a=a*a;
    }
    return c;
}
 
int f[maxn];
Matrix A;
 
int getFail(char* s) {
    int n=strlen(s);
    f[0]=0;
    for(int i=1,k=0;i<n;i++) {
        while(k && s[k]!=s[i]) k=f[k-1];
        if(s[k]==s[i]) k++;
        f[i]=k;
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<=9;j++) {
            int k=i;
            while(k && s[k]!=j+'0') k=f[k-1];
            if(s[k]==j+'0') k++;
            A.mat[i][k]=(A.mat[i][k]+1)%mo;
        }
    }
}
 
char buf[maxn];
int main() {
    int n,m;
    scanf("%d%d%d%s",&n,&m,&mo,buf);
    A.r=m;A.c=m;
    getFail(buf);
    A=MatPow(A,n);
    int ans=0;
    REP(i,0,m-1) ans=(ans+A.mat[0][i])%mo;
    printf("%d\n",ans);
    return 0;
}
