/**************************************************************
    Problem: 1013
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
 
const int maxn=10+5;  
const double eps=1e-8;  
typedef double Matrix[maxn][maxn];  
bool gauss_elimination(Matrix A,int n) {  
    REP(i,0,n-1) {  
        int r=i;  
        REP(j,i+1,n-1)  
            if(fabs(A[j][i]>fabs(A[r][i]))) r=j;  
        if(r!=i) REP(j,0,n) swap(A[r][j],A[i][j]);  
        REP(k,i+1,n-1) {  
            double f=A[k][i]/A[i][i];  
            REP(j,i,n) A[k][j]-=f*A[i][j];  
        }  
    }  
    PER(i,n-1,0) {  
        REP(j,i+1,n-1)  
            A[i][n]-=A[j][n]*A[i][j];  
        if(fabs(A[i][i])<eps) return false;  
        A[i][n]/=A[i][i];  
    }  
    return true;  
}  
 
double st[maxn];
Matrix A;   
int main() {  
    int n;
    double x;
    scanf("%d",&n);
    REP(i,0,n-1) scanf("%lf",&st[i]);  
    REP(i,0,n-1) {
        REP(j,0,n-1) {
            scanf("%lf",&x);
            A[i][j]=2*(x-st[j]);
            A[i][n]+=x*x-st[j]*st[j];
        }
    }
    gauss_elimination(A,n);
    REP(i,0,n-1) {
        if(i) printf(" ");
        printf("%.3lf",A[i][n]);
    }
    printf("\n");
    return 0;  
}  
