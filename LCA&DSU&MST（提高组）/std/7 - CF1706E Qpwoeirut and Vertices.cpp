#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define int long long
#define MAXN (int)(3e5+233)
#define rep(i,l,r) for (int i=l;i<=r;i++)

namespace crq
{

	inline long long read()
	{
		int x=0,f=1;char c;
		while (!isdigit(c=getchar())) if (c=='-') f=-1;
		while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
		return f*x;
	}

	inline int max(int x,int y) { return x>y?x:y; }
	
	inline int zero() { return 0; }
	
	template <typename crq,crq(*op)(crq,crq),crq e()>
	struct Seg
	{
		
		public:
			 
			void init(int n)
			{
				init_pow2();
				h=ceil_log2(n);
				SIZE=1<<h;
				val=std::vector<crq>(SIZE<<1,e());
			}
			
			void modify(int k,crq x)
			{
				k+=SIZE-1;
				val[k]=x;
				for (int i=1;i<=h;i++) pushup(k>>=1);
			}
			
			crq get(int k) { return val[SIZE+k-1]; }
			
			crq query(int l,int r)
			{
				l--;
				crq sl=e(),sr=e();
				l+=SIZE,r+=SIZE;
				while (l<r)
				{
					if (l&1) sl=op(sl,val[l++]);
					if (r&1) sr=op(sr,val[--r]);
					l>>=1,r>>=1;
				}
				return op(sl,sr);
			}
		
		private:
			
			int h=0,SIZE=0,pow2[27];
			std::vector<crq> val;
			
			void init_pow2()
			{
				pow2[0]=1;
				for (int i=1;i<=25;i++) pow2[i]=pow2[i-1]<<1;
			} 
			
			int ceil_log2(int x)
			{
				for (int i=25;i>=1;i--)
					if (pow2[i]>=x&&pow2[i-1]<x)
						return i;
				return 0;
			}
			
			inline void pushup(int now) { val[now]=op(val[now<<1],val[now<<1|1]); }
		
	};
	
}

using crq::read;
using crq::Seg;

struct Edge
{
	int to,nex;
} E[MAXN<<1];
 
int T,n,m,q,cnt,fa[MAXN],siz[MAXN],head[MAXN];
Seg<int,crq::max,crq::zero> s;

inline void add(int u,int v)
{
	E[++cnt].to=v;
	E[cnt].nex=head[u];
	head[u]=cnt;
}

int find(int x) { return (x==fa[x])?x:fa[x]=find(fa[x]); }

void dfs(int x,int f,int t)
{
	if (!s.get(x)&&find(x)==find(x-1)) s.modify(x,t);
	if (!s.get(x+1)&&find(x)==find(x+1)) s.modify(x+1,t);
	for (int i=head[x];i;i=E[i].nex)
		if (E[i].to!=f) dfs(E[i].to,x,t);
}

void merge(int x,int y,int t)
{
	x=find(x),y=find(y);
	if (x==y) return;
	if (siz[x]<siz[y]) swap(x,y);
	fa[y]=x,siz[x]+=siz[y];
	dfs(y,0,t);
	add(x,y),add(y,x);
}

signed main()
{
	cin>>T;
	while (T--)
	{
		cin>>n>>m>>q;
		cnt=0,s.init(n);
		rep(i,1,n) fa[i]=i,head[i]=0,siz[i]=1;
		rep(i,1,m) merge(read(),read(),i);
		rep(i,1,q)
		{
			int a=read(),b=read();
            if (a==b) printf("0 ");
			else printf("%lld ",s.query(a+1,b));
		}
		putchar('\n');
	}
	return 0;
}
