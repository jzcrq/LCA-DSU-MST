#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
#define MAXN (int)(3e5+233)
#define int long long
#define rep(i,l,r) for (int i=l;i<=r;i++)

inline int read()
{
	int x=0,f=1;char c;
	while (!isdigit(c=getchar())) if (c=='-') f=-1;
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}

inline int crq_min(int x,int y) { return x<y?x:y; }

int n,m,ans=1e18,tmp,fa[MAXN],siz[MAXN],X[MAXN],Y[MAXN];

struct Edge
{
	
	int u,v,w;
	
	inline bool operator < (Edge x) { return w<x.w; }
	
} E[MAXN<<2],E2[MAXN<<2];

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

void input()
{
	n=read(),m=read();
	rep(i,1,n) X[i]=read();
	rep(i,1,n) Y[i]=read();
	rep(i,1,m) E[i].u=E2[i].u=read(),E[i].v=E2[i].v=read(),E[i].w=E2[i].w=read();
	rep(i,1,n) E[m+i].u=i,E[m+i].v=n+1,E[m+i].w=X[i];
	rep(i,1,n) E[m+n+i].u=E2[m+i].u=i,E[m+n+i].v=E2[m+i].v=n+2,E[m+n+i].w=E2[m+i].w=Y[i];
}

int MST(Edge e[],int len)
{
	int ret=0;
	sort(e+1,e+len+1);
	rep(i,1,n+2) fa[i]=i,siz[i]=1;
	rep(i,1,len)
		if (find(e[i].u)!=find(e[i].v))
			merge(e[i].u,e[i].v),ret+=e[i].w;
	return ret;
}

signed main()
{
	input();
	ans=crq_min(ans,MST(E,m));
	if (siz[find(1)]!=n) ans=1e18;
	ans=crq_min(ans,MST(E,m+n));
	ans=crq_min(ans,MST(E2,m+n));
	ans=crq_min(ans,MST(E,m+(n<<1)));
	printf("%lld",ans); 
	return 0;
}
