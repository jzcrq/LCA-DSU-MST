#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
using namespace std;
#define int long long
#define MAXN (int)(1e7+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

int n,h,mx,cnt,A[MAXN],pow2[33],ch[MAXN][2];

inline int crq_max(int x,int y) { return x>y?x:y; }

inline int crq_min(int x,int y) { return x<y?x:y; }
	
inline int read()
{
	int x=0,f=1;char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}

void ins(int v)
{
	int x=0;
	per(i,h,0)
	{
		int *y=&ch[x][(v&pow2[i])!=0];
		x=(*y)?(*y):((*y)=++cnt);
	}
}

int dfs2(int x,int y,int v,int dep)
{
	int ret=1e18;
	if (dep<0) return v;
	if (ch[x][0]&&ch[y][0]) ret=crq_min(ret,dfs2(ch[x][0],ch[y][0],v,dep-1));
	if (ch[x][1]&&ch[y][1]) ret=crq_min(ret,dfs2(ch[x][1],ch[y][1],v,dep-1));
	if (!ch[x][0]&&!ch[y][1]) ret=crq_min(ret,dfs2(ch[x][1],ch[y][0],v+pow2[dep],dep-1));
	if (!ch[x][1]&&!ch[y][0]) ret=crq_min(ret,dfs2(ch[x][0],ch[y][1],v+pow2[dep],dep-1));
	return ret;
}

int dfs1(int x,int dep)
{
	int ret=0;
	if (ch[x][0]) ret+=dfs1(ch[x][0],dep-1);
	if (ch[x][1]) ret+=dfs1(ch[x][1],dep-1);
	if (ch[x][0]&&ch[x][1]) ret+=dfs2(ch[x][0],ch[x][1],pow2[dep],dep-1);
	return ret;
}

signed main()
{
	pow2[0]=1;
	rep(i,1,31) pow2[i]=pow2[i-1]<<1ll;
	n=read();
	rep(i,1,n) A[i]=read(),mx=crq_max(mx,A[i]);
	per(i,31,0) if (pow2[i]&mx) { h=i; break; }
	rep(i,1,n) ins(A[i]);
	printf("%lld",dfs1(0,h));
	return 0;
}
