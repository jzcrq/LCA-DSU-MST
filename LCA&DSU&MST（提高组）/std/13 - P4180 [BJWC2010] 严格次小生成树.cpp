#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
#define MAXN (int)(3e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)
#define per(i,r,l) for (int i=r;i>=l;i--)
#define pb push_back
#define mk make_pair

struct Edge
{
	
	int u,v,w;
	
	inline bool operator < (Edge x) { return w<x.w; }
	
} E[MAXN];

int n,m,ans,cst=1e9,fa[MAXN],siz[MAXN];
int lg[MAXN],dep[MAXN],f[MAXN][21],fir[MAXN][21],sec[MAXN][21];
bool vis[MAXN];
vector<pair<int,int>> to[MAXN];
vector<int> tmp;

inline int crq_max(int x,int y) { return x>y?x:y; }

inline int crq_min(int x,int y) { return x<y?x:y; }

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

void dfs(int x)
{
	for (auto y:to[x])
	{
		int c=y.second;
		if (c==f[x][0]) continue;
		fir[c][0]=y.first,f[c][0]=x,dep[c]=dep[x]+1;
		dfs(c);
	}
}

inline void in(int i,int j) { tmp.pb(fir[i][j]),tmp.pb(sec[i][j]); }

inline void get(int &x,int &y)
{
	tmp.pb(x),tmp.pb(y);
	sort(tmp.begin(),tmp.end());
	tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
	x=*tmp.rbegin();
	if (tmp.size()>=2) y=*(++tmp.rbegin());
	while (!tmp.empty()) tmp.pop_back();
}

signed main()
{
	scanf("%lld%lld",&n,&m);
	rep(i,1,n) fa[i]=i,siz[i]=1,lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	rep(i,1,m) scanf("%lld%lld%lld",&E[i].u,&E[i].v,&E[i].w);
	sort(E+1,E+m+1);
	rep(i,1,m)
	{
		int u=E[i].u,v=E[i].v,w=E[i].w;
		if (find(u)!=find(v))
		{
			merge(u,v),ans+=w,vis[i]=1;
			to[u].pb(mk(w,v));
			to[v].pb(mk(w,u));
		}
	}
	dfs(1);
	rep(t,1,20)
		rep(i,1,n)
		{
			f[i][t]=f[f[i][t-1]][t-1];
			in(i,t-1),in(f[i][t-1],t-1);
			get(fir[i][t],sec[i][t]);
		}
	rep(i,1,m)
		if (!vis[i])
		{
			int x=E[i].u,y=E[i].v,mx=0,se=0;
			if (x==y) continue;
			if (dep[x]<dep[y]) swap(x,y);
			while (dep[x]>dep[y])
			{
				in(x,lg[dep[x]-dep[y]]-1);
				get(mx,se);
				x=f[x][lg[dep[x]-dep[y]]-1];
			}
			if (x!=y)
			{
				per(k,lg[dep[x]]-1,0)
					if (f[x][k]!=f[y][k])
					{
						in(x,k),in(y,k);
						get(mx,se);
						x=f[x][k],y=f[y][k];
					}
				in(x,0),in(y,0);
				get(mx,se);
			}
			if (E[i].w==mx) cst=crq_min(cst,E[i].w-se);
			else cst=crq_min(cst,E[i].w-mx);
		}
	printf("%lld",ans+cst);
	return 0;
}
