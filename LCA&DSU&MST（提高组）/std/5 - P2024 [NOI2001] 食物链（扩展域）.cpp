#include <algorithm>
#include <cstdio>
using namespace std;
#define MAXN (int)(2e5+233)

int N,K,ans,fa[MAXN],siz[MAXN];

inline int f(int x) { return x+N; }

inline int g(int x) { return x+(N<<1); }

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
	scanf("%d%d",&N,&K);
	for (int i=1;i<=(N<<1)+N;i++) fa[i]=i,siz[i]=1;
	for (int i=1;i<=K;i++)
	{
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if (x>N||y>N) { ans++; continue; }
		if (opt^2)
		{
			if (find(f(x))==find(y)) ans++;
			else if (find(x)==find(f(y))) ans++;
			else
			{
				merge(x,y);
				merge(f(x),f(y));
				merge(g(x),g(y));
			}
		}
		else
		{
			if (find(x)==find(y)) ans++;
			else if (find(x)==find(f(y))) ans++;
			else
			{
				merge(f(x),y);
				merge(x,g(y));
				merge(g(x),f(y));
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
