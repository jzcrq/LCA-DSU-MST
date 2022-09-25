#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define MAXN (int)(5e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

int n,q,tx,ty,lg[MAXN],siz[MAXN],dep[MAXN],fa[MAXN][21];
vector<int> to[MAXN];

void dfs(int x)
{
	siz[x]=1;
	for (int y:to[x])
	{
		if (dep[y]) continue;
		dep[y]=dep[x]+1,fa[y][0]=x;
		dfs(y);
		siz[x]+=siz[y];
	}
}

int LCA(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	while (dep[x]>dep[y])
		x=fa[x][lg[dep[x]-dep[y]]-1];
	if (x==y) return x;
	per(k,lg[dep[x]]-1,0)
		if (fa[x][k]!=fa[y][k])
			x=fa[x][k],y=fa[y][k];
	tx=x,ty=y;
	return fa[x][0];
}

int son(int x,int y)
{
	while (dep[x]>dep[y]+1)
		x=fa[x][lg[dep[x]-dep[y]-1]-1];
	return x;
}

inline int dis(int x,int y) { return dep[x]+dep[y]-(dep[LCA(x,y)]<<1); }

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
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if (dis(a,c)+dis(b,c)!=dis(a,b))
		{
			printf("0\n");
			continue;
		}
		if (a==c&&b==c)
		{
			printf("%d\n",n);
			continue;
		}
		if (a==c)
		{
			if (LCA(b,c)==c) printf("%d\n",n-siz[son(b,c)]);
			else printf("%d\n",siz[c]);
			continue;
		}
		if (b==c)
		{
			if (LCA(a,c)==c) printf("%d\n",n-siz[son(a,c)]);
			else printf("%d\n",siz[c]);
			continue;
		}
		if (LCA(a,b)==c) printf("%d\n",n-siz[tx]-siz[ty]);
		else if (LCA(a,c)==c) printf("%d\n",siz[c]-siz[son(a,c)]);
		else printf("%d\n",siz[c]-siz[son(b,c)]);
	}
	return 0;
}
