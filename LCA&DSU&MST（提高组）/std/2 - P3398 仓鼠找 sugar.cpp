#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define MAXN (int)(1e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

int n,q,lg[MAXN],dep[MAXN],fa[MAXN][21];
vector<int> to[MAXN];

void dfs(int x)
{
	for (int y:to[x])
	{
		if (dep[y]) continue;
		dep[y]=dep[x]+1;
		fa[y][0]=x;
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

inline int dis(int x,int y)
{
	int lca=LCA(x,y);
	return dep[x]+dep[y]-(dep[lca]<<1);
}

int main()
{
	scanf("%d%d",&n,&q);
	rep(i,1,n) lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	rep(i,1,n-1)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		to[a].push_back(b);
		to[b].push_back(a);
	}
	dep[1]=1;
	dfs(1);
	rep(t,1,20)
		rep(i,1,n)
			fa[i][t]=fa[fa[i][t-1]][t-1];
	rep(i,1,q)
	{
		int a,b,c,d,la,lb;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		la=LCA(a,b),lb=LCA(c,d);
		if (dis(la,c)+dis(la,d)==dis(c,d)||dis(lb,a)+dis(lb,b)==dis(a,b))
			printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
