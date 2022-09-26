#include <algorithm>
#include <cstdio>
using namespace std;
#define MAXN (int)(1e4+514)
#define rep(i,l,r) for (int i=l;i<=r;i++)

struct Edge
{	

	int u,v,w;
	
	inline bool operator < (Edge x) { return w<x.w; }

} E[MAXN<<1];

int n,m,ans,fa[MAXN],siz[MAXN];

inline int crq_max(int x,int y) { return x>y?x:y; }

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

int main()
{
	scanf("%d%d",&n,&m);
	rep(i,1,n) fa[i]=i,siz[i]=1;
	rep(i,1,m) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	sort(E+1,E+m+1);
	rep(i,1,m)
		if (find(E[i].u)!=find(E[i].v))
			ans=crq_max(ans,E[i].w),merge(E[i].u,E[i].v);
	printf("%d",ans);
	return 0;
} 
