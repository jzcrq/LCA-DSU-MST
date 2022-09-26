#include <algorithm>
#include <cstdio>
using namespace std;
#define MAXN 107
#define rep(i,l,r) for (int i=l;i<=r;i++)

int n,fa[MAXN],siz[MAXN];
double x[MAXN],y[MAXN];

int find(int x) { return (x==fa[x])?x:find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

bool check(double k)
{
	k*=2.0;
	rep(i,1,n+2) fa[i]=i,siz[i]=1;
	rep(i,1,n)
	{
		if ((100.0-y[i])*(100.0-y[i])<k*k) merge(i,n+1);
		if ((y[i]+100.0)*(y[i]+100.0)<k*k) merge(i,n+2);
	}
	rep(i,1,n)
		rep(j,i+1,n)
			if ((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<k*k) merge(i,j);
	return find(n+1)!=find(n+2);
}

int main()
{
	scanf("%d",&n);
	rep(i,1,n) scanf("%lf%lf",&x[i],&y[i]);
	double l=0.0,r=1e9+7.0;
	while (l+0.0000001<r)
	{
		double mid=(l+r)/2.0;
		if (check(mid)) l=mid;
		else r=mid;
	}
	printf("%lf",l);
	return 0;
} 
