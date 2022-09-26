#include <cstdio>
#define MAXN (int)(3e4+233)

int T,fa[MAXN],d[MAXN],siz[MAXN];

inline int crq_abs(int x) { return x>0?x:-x; }

int find(int x)
{
	if (x==fa[x]) return x;
	int rt=find(fa[x]);
	d[x]+=d[fa[x]];
	return fa[x]=rt;
}

void merge(int x,int y)
{
	x=find(x),y=find(y);
	fa[x]=y,d[x]=siz[y],siz[y]+=siz[x];
}

int main()
{
	for (int i=1;i<=3e4;i++) fa[i]=i,siz[i]=1;
	scanf("%d",&T);
	while (T--)
	{
		char opt;int i,j;
		scanf(" %c%d%d",&opt,&i,&j);
		if (opt=='M') merge(i,j);
		else if (find(i)==find(j)) printf("%d\n",crq_abs(d[i]-d[j])-1);
		else printf("-1\n");
	}
	return 0;
}
