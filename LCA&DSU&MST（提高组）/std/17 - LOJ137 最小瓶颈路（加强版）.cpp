#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define MAXN (int)(2e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)

const int mod=1e9+7;
int N,n,m,q,ans,fa[MAXN],siz[MAXN],head[MAXN];
int dep[MAXN],val[MAXN],f[MAXN],son[MAXN],sz[MAXN],top[MAXN];
int A,B,C,P;
vector<int> to[MAXN];

struct Edge
{
	
	int u,v,w;
	
	inline bool operator < (Edge x) { return w<x.w; }
	
} E[MAXN<<1];

inline int rnd() { return A=(A*B+C)%P; }

inline int crq_max(int x,int y) { return x>y?x:y; }

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

inline void merge(int i)
{
	int x=E[i].u,y=E[i].v,rx=find(x),ry=find(y);
	if (rx==ry) return;
	if (siz[rx]>siz[ry]) swap(rx,ry);
	fa[rx]=ry,siz[ry]+=siz[rx];
	f[head[rx]]=f[head[ry]]=++n;
	to[n].push_back(head[rx]);
	to[n].push_back(head[ry]);
	head[ry]=n,val[n]=E[i].w;
}

void dfs1(int x,int depth)
{
	int mx=-1;
	dep[x]=depth,sz[x]=1;
	for (int y:to[x])
	{
		dfs1(y,depth+1);
		sz[x]+=sz[y];
		if (sz[y]>mx) mx=sz[y],son[x]=y;
	}
}

void dfs2(int x,int tf)
{
	top[x]=tf;
	if (!son[x]) return;
	dfs2(son[x],tf);
	for (auto y:to[x]) if (y!=son[x]) dfs2(y,y);
}

inline int LCA(int x,int y)
{
	while (top[x]!=top[y])
		if (dep[top[x]]>=dep[top[y]]) x=f[top[x]];
		else y=f[top[y]];
	return dep[x]<dep[y]?x:y;
}

int main()
{
	scanf("%d%d",&n,&m);N=n;
	rep(i,1,n) fa[i]=head[i]=i,siz[i]=1;
	rep(i,1,m) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	sort(E+1,E+m+1);
	rep(i,1,m)
		if (find(E[i].u)!=find(E[i].v)) merge(i);
	dfs1(n,1),dfs2(n,n);
	scanf("%d%d%d%d%d",&q,&A,&B,&C,&P);
	while (q--)
	{
		int u=rnd()%N+1,v=rnd()%N+1;
		ans=(ans+val[LCA(u,v)])%mod;
	}
	printf("%d",ans);
	return 0;
} 
