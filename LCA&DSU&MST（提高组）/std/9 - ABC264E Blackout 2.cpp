#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <map>
using namespace std;
#define MAXN (int)(5e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)

int n,m,q,ans,e,X[MAXN],fa[MAXN],siz[MAXN],city[MAXN],conx[MAXN],cony[MAXN],opt[MAXN];
bool elec[MAXN],usf[MAXN];

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]<siz[y]) swap(x,y);
	if (elec[x]^elec[y])
	{
		if (elec[x]) ans+=city[y],elec[y]=1;
		else ans+=city[x],elec[x]=1;
	}
	siz[x]+=siz[y],city[x]+=city[y];
	fa[y]=x,elec[x]|=elec[y];
}

int main()
{
	scanf("%d%d%d",&n,&m,&e);
	rep(i,1,n+m) fa[i]=i,siz[i]=1,city[i]=(i<=n),elec[i]=(i>n);
	rep(i,1,e) scanf("%d%d",&conx[i],&cony[i]);
	scanf("%d",&q);
	rep(i,1,q) scanf("%d",&X[i]),usf[X[i]]=1;
	rep(i,1,e)
	{
		if (usf[i]) continue;
		merge(conx[i],cony[i]);
	}
	per(i,q,1)
	{
		opt[i]=ans;
		merge(conx[X[i]],cony[X[i]]);
	}
	rep(i,1,q) printf("%d\n",opt[i]);
	return 0;
} 
