#include <algorithm>
#include <cstdio>
#include <stack>
using namespace std;
#define MAXN 107
#define rep(i,l,r) for (int i=l;i<=r;i++)

struct Edge
{
	
	int u,v,w;
	
	inline bool operator < (Edge x) { return w<x.w; }
	
} E[MAXN*MAXN];

int T,n,m,ans,fa[MAXN],siz[MAXN];
stack<int> sta;

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

void R()
{
	ans=0;
	while (!sta.empty()) sta.pop();
	scanf("%d%d",&n,&m);
	rep(i,1,n) fa[i]=i,siz[i]=1;
	rep(i,1,m) scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	sort(E+1,E+m+1);
	rep(i,1,m)
	{
		if (find(E[i].u)==find(E[i].v)) continue;
		sta.push(i);
		int l=i,r=i;
		while (E[r+1].w==E[l].w)
		{
			r++;
			if (find(E[r].u)!=find(E[r].v)) sta.push(r);
		}
		while (!sta.empty())
		{
			int j=sta.top();
			sta.pop();
			if (find(E[j].u)!=find(E[j].v))
				merge(E[j].u,E[j].v),ans+=E[j].w;
			else
			{
				printf("Not Unique!\n");
				return;
			}
		}
		i=r;
	}
	printf("%d\n",ans);
}

int main()
{
	scanf("%d",&T);
	while (T--) R();
	return 0;
}
