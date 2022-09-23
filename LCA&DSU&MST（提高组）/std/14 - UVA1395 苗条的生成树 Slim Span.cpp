#include <algorithm>
#include <cstdio>
using namespace std;
#define MAXN 107
#define rep(i,l,r) for (int i=l;i<=r;i++)

struct Edge
{
	
	int u,v,w;
	
	inline bool operator < (Edge x) { return w<x.w; }
	
} E[MAXN*MAXN];

int n,m,ans,fa[MAXN],siz[MAXN];

inline int crq_min(int x,int y) { return x<y?x:y; }

inline int crq_max(int x,int y) { return x>y?x:y; }

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

bool R()
{
	ans=1e9;
	scanf("%d%d",&n,&m);
	if (!n&&!m) return 0;
	rep(i,1,m) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	sort(E+1,E+m+1);
	rep(i,1,m-n+2)
	{
		int mi=1e9,mx=0,cnt=0;
		rep(j,1,n) fa[j]=j,siz[j]=1;
		rep(j,i,m)
			if (find(E[j].u)!=find(E[j].v))
				merge(E[j].u,E[j].v),
				mi=crq_min(mi,E[j].w),
				mx=crq_max(mx,E[j].w),cnt++;
		printf("!%d %d\n",cnt,mx-mi);
		if (cnt==n-1) ans=crq_min(ans,mx-mi);
	}
	printf("%d\n",(ans==1e9)?-1:ans);
	return 1;
}

int main()
{
	while (R()) ;
	return 0;
}
