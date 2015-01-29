# 2009 Wuhan: Box Relations
## Summary

空间中有N(N&lt;=1000)个立方体，按照如下格式给出他们之间的关系：

I i j:立方体i与立方体j相交

X i j:立方体i所有的x坐标小于立方体j所有的x坐标

Y i j:立方体i所有的y坐标小于立方体j所有的x坐标

Z i j:立方体i所有的z坐标小于立方体j所有的x坐标

要求出一组合法的立方体放置方案,若冲突则输出IMPOSSIBLE.
## Solution

可以转化为图论模型,然后在X,Y,Z三个方向上,根据给出的空间关系,分别进行拓扑排序.以X轴为例:每个立方体用两个坐标表示:x<sub>1</sub>,x<sub>2</sub>, 在图上都有相应的节点,如果节点i的值小于节点j的值,那么i到j就有一条边.

对于所有的x<sub>i1</sub>至x<sub>i2</sub>均有一条边.

如果有关系I i j,那么x<sub>i1</sub>至x<sub>j2</sub>,x<sub>j1</sub>至x<sub>i2</sub>连边.

如果有X i j,那么x<sub>i2</sub>至x<sub>j1</sub>连边.

求出拓扑序,每个节点的拓扑值就是其坐标.按照这个方法可以求出Y,Z方向上的坐标值. 
