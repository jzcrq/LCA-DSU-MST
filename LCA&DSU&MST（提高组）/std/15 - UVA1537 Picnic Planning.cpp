#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdio>
#include <map>
using namespace std;
#define MAXN 33
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define pb push_back
#define mk make_pair

struct Con
{
	
	int u,v,w;
	
	inline bool operator < (Con x) { return w<x.w; }
	
} c[MAXN*MAXN];

struct Edge
{
	int to,nex,val;
	bool cut;
} E[MAXN*MAXN];

int T,n,m,k,ans,deg,fa[MAXN],siz[MAXN];
int cnt=1,head[MAXN];
int mx[MAXN];
bool vis[MAXN];
map<string,int> id;
vector<pair<int,int>> near;
pair<int,int> sel;

inline void add(int u,int v,int w)
{
	E[++cnt].to=v;
	E[cnt].val=w;
	E[cnt].cut=0;
	E[cnt].nex=head[u];
	head[u]=cnt;
}

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

void dfs(int x,int ft)
{
	for (int i=head[x];i;i=E[i].nex)
	{
		if (E[i].cut) continue;
		int y=E[i].to;
		if (y==ft) continue;
		mx[y]=(E[i].val>=E[mx[x]].val)?i:mx[x];
		dfs(y,x);
	}
}

void R()
{
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	near.clear(),id.clear();
	ans=deg=0,n=id["Park"]=cnt=1,E[0].val=-1e9;
	scanf("%d",&m);
	rep(i,1,m)
	{
		string a,b;
		cin>>a>>b;
		if (!id[a]) id[a]=++n;
		if (!id[b]) id[b]=++n;
		c[i].u=id[a],c[i].v=id[b];
		scanf("%d",&c[i].w);
	}
	rep(i,1,n) fa[i]=i,siz[i]=1;
	sort(c+1,c+m+1);
	rep(i,1,m)
	{
		if (c[i].u==1||c[i].v==1)
		{
			if (c[i].u==1) near.pb(mk(c[i].w,c[i].v));
			else near.pb(mk(c[i].w,c[i].u));
			continue;
		}
		if (find(c[i].u)!=find(c[i].v))
			ans+=c[i].w,add(c[i].u,c[i].v,c[i].w),add(c[i].v,c[i].u,c[i].w),merge(c[i].u,c[i].v);
	}
	sort(near.begin(),near.end());
	for (auto i:near)
	{
		int w=i.first,y=i.second;
		if (vis[y]) continue;
		if (find(1)!=find(y))
			ans+=w,add(1,y,w),add(y,1,w),merge(1,y),vis[y]=1,deg++;
	}
	scanf("%d",&k);
	while (deg<k)
	{
		memset(mx,0,sizeof(mx));
		sel=mk(0,0);
		for (int i=head[1];i;i=E[i].nex) dfs(E[i].to,1);
		for (auto i:near)
		{
			int w=i.first,y=i.second;
			if (vis[y]||!mx[y]) continue;
			sel=(w-E[mx[y]].val<sel.first-E[mx[sel.second]].val)?i:sel;
		}
		if (sel.first-E[mx[sel.second]].val>=0) break;
		E[mx[sel.second]].cut=E[mx[sel.second]^1].cut=1,ans+=sel.first-E[mx[sel.second]].val;
		add(1,sel.second,sel.first),add(sel.second,1,sel.first);
		vis[sel.second]=1,deg++;
	}
	printf("Total miles driven: %d\n",ans);
	if (T) putchar('\n');
}

int main()
{
	scanf("%d",&T);
	while (T--) R();
	return 0;
}
