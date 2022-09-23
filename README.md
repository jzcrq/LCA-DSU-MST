# LCA-DSU-MST

---

[TOC]

### $\text {LCA} $

---

#### 前置知识

起码会个倍增树剖吧。

---

#### 时间复杂度

单次查询
$\mathcal{O}(1) \sim \mathcal{O}(\log n)$
，取决于实现方式。

---

#### 树上差分

$$
\large dis_{u,v}=dep_u+dep_v-2 \cdot dep_{lca}
$$

$$
\large sum_{u,v}=sum_{rt,u}+sum_{rt,v}-sum_{rt,lca}-sum_{rt,fa(lca)}
$$

常用于解决于树上路径相关的计数问题，用哪条就看要不要拿 
$\text {LCA}$ 
。

**[P4427 [BJOI2018]求和](https://www.luogu.com.cn/problem/P4427)**

---

#### 最小瓶颈路

配合
$\text {Kruskal}$
重构树解决最小瓶颈路类型问题。

常见问题格式为第
$i$ 
次操作使两部分连通等。

具体见 
$\text{Kruskal} $
重构树部分。

---

#### 树上路径相交

对于 
$\large x=lca(a,b),y=lca(c,d) $ 
，有：
$x$
在路径
$c \to d$ 
上**或** $y$ 在路径 
$a \to b$
上。

对于 
$\large dis(x,a)+dis(x,b)=dis(a,b) $ 
，有：
$x$ 
在路径
$a \to b$ 
上。

**[P3398 仓鼠找 sugar](https://www.luogu.com.cn/problem/P3398)**

---

#### 无根树 $\text {LCA} $

对于一棵无根树，如有 
$c$ 
在路径 
$a \to b $ 上，则以任意与 
$c$ 
路径上不经过点
$a$ 
与 
$b$ 
的点 
$x$ 
为根时，有 
$\large lca(a,b)=c $
。

**[P6374 「StOI-1」树上询问](https://www.luogu.com.cn/problem/P6374)**

---

#### 小结

总之，遇到的树上路径问题，第一时间想到的就应该是 
$\text{LCA}$
，再有就是考虑利用树剖把树上问题转成关于 
$DFS$ 
序的序列问题。

> 树剖可耻但有用。—— $\text {crq}$ 

省选题可能还有 
$\text {LCT}$
，但超出了我们的讨论范畴。

当然，也有可能确实和 
$\text{LCA}$ 
无关，再考虑是否与树的直径，树的重心的性质相关，再者一般就与树性质无关了。

---

### $\text {DSU} $

---

#### 前置知识

路径压缩，按秩合并，启发式合并。

（线段树）

（二分答案）

---

#### 时间复杂度

仅路径压缩，平均时间复杂度
$\mathcal{O}(m \alpha(m,n))$
，最坏时间复杂度 
$\mathcal{O}(m \log n)$
。

仅按秩合并 / 启发式合并，平均与最坏时间复杂度均为
$\mathcal{O}(m \log n)$
。

路径压缩 + 按秩合并 / 启发式合并，平均与最坏时间复杂度均为 
$\mathcal{O}(m \alpha(m,n))$
。

按秩合并 / 启发式合并的并查集树高最坏与
$\log n$ 
同级。

启发式合并时每次合并总是遍历较小的并查集，遍历最坏总时间复杂度为
$\mathcal{O}(n \log n)$
。

求无向图生成森林的 
$\text{Boruvka}$ 
算法与其思路类似，时间复杂度为
$\mathcal{O}(m \log n \cdot \alpha(m,n))$
；常用于边权由点权决定的情况，便于将时间复杂度优化至 
$\mathcal{O}(n \log n \cdot \alpha(m,n))$
，具体见 
$\text {MST}$
部分。

---

#### 带权并查集

让并查集的边带上权值。

如果进行路径压缩，则要求维护的权值对应的运算满足结合律。

通常维护的运算有普通的加法乘法，带模加法，
$\max , \min$ 
等。

带模加法是表示环形二元关系的常见方式，这种问题也常用扩展域的方式解决。

模数为
$2$ 
的带模加法常用异或表示。

带权并查集往往规定了合并方向，不能够按秩合并 / 启发式合并。

**[P1196 [NOI2002] 银河英雄传说](https://www.luogu.com.cn/problem/P1196)**

**[P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)**

---

#### 扩展域

如果每一个元素与其它元素至多有 
$x$ 
种关系，可以用
$x+1$ 
组并查集来维护关系。

本质上就是二维并查集。

空间复杂度为
$\mathcal{O}(nx)$
，时间复杂度取决于加边方式。

虽然复杂度劣于带权并查集，但是能更方便应付多元素关系。

与带权并查集一样，如果进行路径压缩，则要求维护的权值对应的运算满足结合律。

**[P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)**

---

#### 连通时间戳

题目形式是求目标在第
$i$ 
次加边时连通，目标可能是两点，也可能是一个标号连续区间内的所有点。

具体题意如下：

> 初始时有 $n$ 个孤立点。
>
> 接下来有 $m$ 次加边操作，第 $i$ 次操作在 $a_i$ 和 $b_i$ 间加一条无向边。
>
> 接下来有 $q$ 次询问，第 $i$ 次询问 $u_i$ 和 $v_i$ 最早在第几次加边后连通。
可以考虑以时间戳为边权建 
$\text {MST}$
：

在第 
$i$ 
次加边时，如果 
$a_i$ 
与
$b_i$
不连通，在
$\text {MST}$ 
中给 
$a_i$ 
和 
$b_i$
连一条边。

答案是
$u_i$ 
与
$v_{i}$ 
两点在 
$\text {MST}$ 
中路径上的边权最大值。

用倍增或树剖维护，时间复杂度为
$\mathcal{O}(n \log n)$
。

是最小瓶颈路问题，可以用 
$\text {Kruskal}$ 
重构树解决，复杂度相同。

也可以将询问离线，在并查集启发式合并时遍历较小的并查集处理询问，复杂度相同。

**[P1967 [NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)**

询问从两点变成标号连续区间的话，可以考虑用线段树维护标号连续点之间最早连通时间戳，每个点只会被打上一个询问，用类似刚才的离线算法的方法就能解决，并且现在它变成了在线算法。

**[CF1706E Qpwoeirut and Vertices](https://www.luogu.com.cn/problem/CF1706E)**

**[题解](https://jzcrq.blog.luogu.org/cf1706e-qpwoeirut-and-vertices-ti-xie)**

---

#### 断边时间戳

对于两点在第
$i$ 
次断边切断之类的问题，先把不会切断的边连好，然后再倒着把要断的边连上，改断边为加边。

**[P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)**

**[ABC264E Blackout 2](https://atcoder.jp/contests/abc264/tasks/abc264_e)**

---

#### 小结

并查集薄纱连通性问题，不能薄纱就试试离线。

因为其复杂度优秀，对于部分正解较难想的问题，可以考虑试图将其转化为连通性问题，如：

**[ABC181F Silver Woods](https://atcoder.jp/contests/abc181/tasks/abc181_f)**

评分是两千，但其实可以二分答案 +
$\text {DSU}$ 
日过去。

~~愚蠢的日本人。~~

至于较大时并查集可以配合离散化食用。

有时候我们会遇到并查集维护的值域在改变的情况，可以考虑记录两个数组表示值域与祖先的相互映射，可以在
$\mathcal{O}(\alpha(m,n))$
的时间复杂度内实现值域平移，如：

~~**[P4117 [Ynoi2018] 五彩斑斓的世界](https://www.luogu.com.cn/problem/P4117)**~~

提高应该不考，别写。

---

### $\text{MST}$

---

#### 前置知识

$\text {Kruskal , Boruvka , LCA , DSU 。}$

（裸树形 
$\text {dp}$）

（
$\text {01Trie}$
）

---

#### 时间复杂度

$\text {Kruskal}$ 
算法复杂度瓶颈在排序算法上，复杂度为
$\mathcal{O}(m \log m) \sim \mathcal{O}(m {\alpha(m,n)})$
，是 
$\text{MST}$ 
的最常用求法。

$\text {Prim}$ 
暴力时间复杂度为 
$\mathcal{O}(n^2+m)$
，二叉堆优化复杂度是 
$\mathcal{O}(n+m) \log n$
，$\text {Fibonacci}$ 
堆优化复杂度是 
$\mathcal{O}(n \log n + m)$。

信我，别写 
$\text{Prim}$。

$\text{Boruvka}$ 
算法时间复杂度为
$\mathcal{O}(m \log n \cdot \alpha(m,n))$
，要求图中各边的边权各不相等（可以用标号作为第二关键字比较来跑有相等边权的图）。

---

#### 最小树形图

其实就是有向图
$\text {MST}$。

可以用朱刘算法
$\mathcal{O}(nm)$ 
解决，也能用
$\text {tarjan}$ 
优化到
$\mathcal{O}(m + n \log n)$
，目测都不考。

**[P4716 【模板】最小树形图](https://www.luogu.com.cn/problem/P4716)**

---

#### 唯一 $\text {MST}$

跑 
$\text {Kruskal}$ 
时设当前相同权值的可以添加进 
$\text {MST}$ 
的边有 
$a$ 
条，实际添加进
$\text {MST}$ 
的边有
$b$ 
条，当
$a > b$ 
时，该图
$\text {MST}$ 
不唯一。

**[POJ1679 The Unique MST](http://poj.org/problem?id=1679)**

---

#### 次小生成树

对于每条不在
$\text {MST}$
上的边
$e=(u,v,w)$
，求出 
$u,v$ 
路径上权值最大边
$e'$
，用 
$e'$ 
替换
$e$ 
即为非严格次小生成树，可以用倍增解决。

在倍增时顺手维护
$u,v$ 
路径上的严格次大边权，只用它作为
$e$ 
来替换 
$e'$ 
即可求出严格次小生成树。

时间复杂度为
$\mathcal{O}(m \log m)$
。

**[P4180 [BJWC2010] 严格次小生成树](https://www.luogu.com.cn/problem/P4180)**

---

#### 极差最小生成树

用第
$1 \leq i \leq m-n+1$ 
条边作为最小权值边（可以看作把前
$i-1$ 
小的边删去）求
$\text {MST}$
，其中最大权值边与最小权值边的权值差最小的一棵
$\text {MST}$ 
就是这张图的极差最小生成树。

时间复杂度为
$\mathcal{O}(m^2 \log m) \sim \mathcal{O}(m^2 \alpha(m,n))$
。

**[UVA1395 苗条的生成树 Slim Span](https://www.luogu.com.cn/problem/UVA1395)**

本题存在
$\text {LCT}$
解法，时间复杂度为
$\mathcal{O}(m \log m)$
，超纲。

**[P4234 最小差值生成树](https://www.luogu.com.cn/problem/P4234)**

---

#### 瓶颈生成树

$\text{MST}$ 
一定是瓶颈生成树，
$\text {MST}$
上 
$u,v$
两点间的路径是
$u,v$ 
两点间的一条最小瓶颈路 。

这两条性质都是充分不必要的。

**[P1547 [USACO05MAR]Out of Hay S](https://www.luogu.com.cn/problem/P1547)**

Tips：这题原题面是求瓶颈生成树的最大权值边，但是搬到洛谷上的时候直接用最小生成树代替了，变成了裸题。

---

#### 最小度限制生成树

对于一张图求规定一个节点度为 
$K$ 
（或者 
$\geq K$
）的
$\text {MST}$
。

先对度限制节点以外的图建 
$\text {MST}$
，再考虑连通分量到限制节点连权值最小边。

连不了就是无法构成生成树，连通分量超过 
$K$ 
就是无法在度数限制下构成生成树。

否则我们就求出了关于度限制节点的最小度生成树。

设当前限制节点度数为 
$X$
，再以限制节点为根做
$K-X$ 
次树形
$\text {dp}$
：每次遍历根节点不在
$\text {MST}$
上的边，求另一头的节点在当前
$\text {MST}$ 
内到根路径上的最大权值边，记为
$f_i$
。

然后用与根相邻的边替换 
$f_i$
，替换时贪心让 
$\text {MST}$ 
总权值最小就好。

如果做不完
$K-X$ 
次树形
$\text {dp}$
就无边可换了，说明无法在度数限制下构成生成树。

否则我们就求出了关于度限制节点的最小度限制生成树。

时间复杂度是
$\mathcal{O}(m \log m + Kn)$ 的。

**[UVA1537 Picnic Planning](https://www.luogu.com.cn/problem/UVA1537)**

有复杂度与 
$\text {Kruskal}$ 
算法同级的解法，目测不考。

**[P5633 最小度限制生成树](https://www.luogu.com.cn/problem/P5633)**

---

#### $\text {Boruvka}$

$\mathcal{O}(m \log n \cdot \alpha(m,n))$ 
的复杂度在
$\text {MST}$ 
算法中平平无奇，但不妨看看这个复杂度是怎么来的。

$\text {Boruvka}$ 
算法在每一轮扫描中遍历
$m$ 
条边，确定图中每个连通块向外伸出的边权最小边，每次扫描连通块起码减半，所以至多扫描
$\log n$ 
轮。

如果我们在每轮贪最小边的复杂度能降低，整个算法的复杂度也就能降低。

所以
$\text {Boruvka}$ 
算法经常用于边权可以由点权推出的情况，设法利用性质将每轮贪心复杂度从
$\mathcal{O}(m \alpha(m,n))$ 
降至
$\mathcal{O}(n)$
。

其实写出完整的 
$\text {Boruvka}$ 
算法的情况很少，更多是利用它的思想。

**[CF888G Xor-MST](https://www.luogu.com.cn/problem/CF888G)**

---

#### $\text {Kruskal}$ 重构树

对于
$n$ 
点 
$m$ 
边无向图，我们初始化
$n$ 
个孤立的节点，然后按照
$\text {Kruskal}$  
算法将这些节点依次连通。

但连通方式并非直接加边，而是新建一个节点，将原来两个节点向新节点连边。

最后构成一棵点数为
$2n-1$ 
的树，即 
$\text {Kruskal}$ 
重构树。

在合并时，我们可以让新建的节点带上点权。

如让新建节点以它代表的原图的边的边权作为点权，则有：
$$
\large \text {原图两点最小瓶颈路上最大边权} = \text {MST 上两点路径上最大边权} = \text{Kruskal 重构树上两点 LCA 点权}
$$
让连通时间戳作为点权即可在线支持连通时间戳问题。

**[LOJ137 最小瓶颈路（加强版）](https://loj.ac/p/137)**

**[P1967 [NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)**

**[CF1706E Qpwoeirut and Vertices](https://www.luogu.com.cn/problem/CF1706E)**

**[P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)**

**[ABC264E Blackout 2](https://atcoder.jp/contests/abc264/tasks/abc264_e)**

---

#### 小结

看着一堆板子，其实都是贪心。

> 图论就是贪贪贪。—— $\text {crq}$

提高考 
$\text {MST}$ 
不是 
$\text {T4}$
基本都是板子吧吧吧......

所以考 
$\text {MST}$
概率不大？

其实次小生成树在提高大纲里。

$\text {Kruskal}$ 
重构树在线薄纱与权值，时间戳相关连通问题。

没了吧吧吧......

**[总题单](https://www.luogu.com.cn/training/226075)**
