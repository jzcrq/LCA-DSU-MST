#include <algorithm>
#include <vector>
#include <cstdio>
#include <stack>
using namespace std;
#define MAXN (int)(5e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)

int n,m,k,ans,fa[MAXN],siz[MAXN];
bool book[MAXN];
vector<int> to[MAXN];
stack<int> sta,opt;

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	ans--;
	if (siz[x]>siz[y]) swap(x,y);
	fa[x]=y,siz[y]+=siz[x];
}

int main()
{
	scanf("%d%d",&n,&m);
	rep(i,0,n-1) fa[i]=i,siz[i]=1;
	rep(i,1,m)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		to[x].push_back(y);
		to[y].push_back(x);
	}
	scanf("%d",&k);
	rep(i,1,k)
	{
		int x;
		scanf("%d",&x);
		sta.push(x);
		book[x]=1;
	}
	ans=n-k;
	rep(x,0,n-1)
		for (int y:to[x])
			if (!book[x]&&!book[y]) merge(x,y);
	while (!sta.empty())
	{
		int x=sta.top();
		sta.pop();
		opt.push(ans);
        ans++;
		for (int y:to[x])
			if (book[x]&&!book[y]) merge(x,y);
		book[x]=0;
	}
    opt.push(ans);
	while (!opt.empty()) printf("%d\n",opt.top()),opt.pop();
	return 0;
}
