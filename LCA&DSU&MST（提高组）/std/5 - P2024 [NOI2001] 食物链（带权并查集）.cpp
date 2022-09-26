#include <cstdio>
#define MAXN (int)(5e4+233)

int N,K,ans,fa[MAXN],d[MAXN];

int find(int x)
{
	if (x==fa[x]) return x;
	int rt=find(fa[x]);
	d[x]=(d[x]+d[fa[x]])%3;
	return fa[x]=rt;
}

int main()
{
	scanf("%d%d",&N,&K);
	for (int i=1;i<=N;i++) fa[i]=i;
	for (int i=1;i<=K;i++)
	{
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if (x>N||y>N) { ans++; continue; }
		find(x),find(y);
		if (opt^2)
		{
			if (fa[x]==fa[y]&&d[x]!=d[y]) ans++;
			else if (fa[x]!=fa[y]) d[fa[x]]=(d[y]-d[x]+3)%3,fa[fa[x]]=fa[y];
		}
		else
		{
			if (x==y) ans++;
			else if (fa[x]==fa[y]) ans+=((d[x]-d[y]+3)%3!=1);
			else d[fa[x]]=(4-d[x]+d[y])%3,fa[fa[x]]=fa[y];
		}
	}
	printf("%d\n",ans);
	return 0;
} 
