# 2009 Wuhan: Exclusive-OR
## Summary

有n(n&lt;=20000)个未知的整数X<sub>0</sub>,X<sub>1</sub>,X<sub>2</sub>...X<sub>n-1</sub>，有以下Q个(Q&lt;=40000)操作：

* I p v&nbsp;:告诉你X<sub>p</sub>=v
* I p q v&nbsp;:告诉你X<sub>p</sub> Xor X<sub>q</sub>=v
* Q k p1 p2 … pk&nbsp;: 询问 X<sub>p1</sub> Xor X<sub>p2</sub> .. Xor X<sub>pk</sub>， k不大于15。

## Solution

由于异或运算满足很多特殊的性质，尤其是交换律，传递性，因此可以使用并查集维护这个集合。并查集为树状结构。设fa[x]为x结点的父亲，设ve[x]为x Xor fa[x]的值。

最核心的部分就是实现并查集的扩展。

在并查集进行压缩路径的时候，明显有：fa[x] = fa[pref]，之后就有ve[x] = ve[pref] ^ ve[x]，pref为压缩之前x结点的父亲，通过递归计算可以得到。

合并的时候，假设已知a Xor b = v，且a，b已经压缩路径，得到其父亲结点分别为pa，pb，那么fa[pa]=pb，且ve[a] = ve[a] Xor ve[b] Xor v。

有一个比较麻烦的问题需要解决。对于I p v这种对单个数字的操作需要另外处理。虽然I p v是对单个数字操作，但是可以认为存在一个“虚点”X<sub>n</sub>=0，由于任何数与0异或等于自己本身，因此I p v相当于I p n v。注意，合并时必须要使X<sub>n</sub>作为父亲，X<sub>p</sub>作为X<sub>n</sub>的儿子。

最后的难题就是查询了。对于X<sub>p1</sub> Xor X<sub>p2</sub> .. Xor X<sub>pk</sub>，分别找出在并查集中位于同一个集合的数字，如果该集合的数字有奇数个，且这个集合里面没有X<sub>n</sub>，那么意味着这个集合不能算出来，返回I don't know。否则将各个集合的异或值再异或起来，可得查询值。

为什么集合的数字有奇数个就不能算出来呢？根据我们并查集ve数组的定义，ve[x]保存的是x与其父亲的异或值。由于经过压缩路径，因此树的深度只有一层。会有两种情况：

1. 需要计算的集合没有树根。假设a,b,c,d,e在同一个集合中，要求a ^ b ^ c ^ d ^ e，且并查集中树根为r，那么通过ve数组，我们知道ve[a] = r ^ a, ve[b] = r ^ b, ve[c] = r ^ c..。把这些数字异或起来，是r xor a ^ r ^ b ^ r ^ c ^ r ^ d ^ r ^ e ^ r。r有奇数个，不能消去。但是如果有偶数个r，也就是待计算的集合有偶数个数字，由于r ^ r = 0，刚好消去，是可以计算出a^b^c^d^e来的。
2. 需要计算的集合含有树根。假设a,b,c,d,r在同一个集合中，要求a ^ b ^ c ^ d ^ r，且并查集中树根为r，那么通过ve数组，我们知道ve[a] = r ^ a, ve[b] = r ^ b, ve[c] = r ^ c..。把这些数字异或起来，是r xor a ^ r ^ b ^ r ^ c ^ r ^ d ^ r。r有偶数个，刚好把需要多的一个r消去了。但是如果有奇数个r，也就是待计算的集合有偶数个数字，r不会被消去，是可以计算出a^b^c^d^r来的。

但是，如果集合中的数字包含X<sub>n</sub>，由于已知X<sub>n</sub>=0，因此无论多了一个0还是少了一个0，异或的结果不变，因此可以计算。

