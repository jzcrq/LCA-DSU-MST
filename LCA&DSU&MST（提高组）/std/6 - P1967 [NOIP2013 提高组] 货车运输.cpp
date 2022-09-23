#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
#define MAXN (int)(1e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)

int n,m,q,fa[MAXN],siz[MAXN],ans[MAXN];
vector<pair<int,int>> to[MAXN];
vector<int> son[MAXN];

struct Edge
{
	
	int x,y,z;
	
	inline bool operator < (Edge e) { return z>e.z; }
	
} E[MAXN<<1];

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void dfs(int x,int y,int z)
{
	for (auto t:to[y])
		if (find(t.second)==x)
			ans[t.first]=z;
	for (auto t:son[y]) dfs(x,t,z);
}

void merge(int i)
{
	int x=E[i].x,y=E[i].y,z=E[i].z; 
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]>siz[y]) swap(x,y);
	dfs(y,x,z);
	fa[x]=y,siz[y]+=siz[x];
	son[y].push_back(x);
}

int main()
{
	scanf("%d%d",&n,&m);
	rep(i,1,n) fa[i]=i;
	rep(i,1,m) scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].z);
	scanf("%d",&q);
	rep(i,1,q)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		to[x].push_back(make_pair(i,y));
		to[y].push_back(make_pair(i,x));
		siz[x]++,siz[y]++;
	}
	sort(E+1,E+m+1);
	rep(i,1,m) merge(i);
	rep(i,1,q) printf("%d\n",ans[i]?ans[i]:-1); 
	return 0;
} 
