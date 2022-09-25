#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
#define MAXN (int)(3e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

const int mod=998244353;
int n,m,lg[MAXN],dep[MAXN],fa[MAXN][21],f[MAXN][51];
vector<int> to[MAXN];

inline int read()
{
	int x=0,f=1;char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}

void dfs(int x)
{
	for (int y:to[x])
	{
		if (dep[y]) continue;
		int tmp=1;
		dep[y]=dep[x]+1,fa[y][0]=x;
		rep(i,1,50) f[y][i]=(f[x][i]+(tmp=(tmp*(dep[y]-1)%mod)))%mod;
		dfs(y);
	}
}

int LCA(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	while (dep[x]>dep[y]) x=fa[x][lg[dep[x]-dep[y]]-1];
	if (x==y) return x;
	per(k,lg[dep[x]]-1,0)
		if (fa[x][k]!=fa[y][k])
			x=fa[x][k],y=fa[y][k];
	return fa[x][0];
}

signed main()
{
	n=read();
	rep(i,1,n) lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	rep(i,1,n-1)
	{
		int a=read(),b=read();
		to[a].push_back(b);
		to[b].push_back(a);
	}
	dep[1]=1;
	dfs(1);
	rep(t,1,20)
		rep(i,1,n)
			fa[i][t]=fa[fa[i][t-1]][t-1];
	m=read();
	rep(i,1,m)
	{
		int a=read(),b=read(),k=read(),lca=LCA(a,b);
		printf("%lld\n",((f[a][k]+f[b][k]-f[lca][k]-f[fa[lca][0]][k])%mod+mod)%mod);
	}
	return 0;
}
