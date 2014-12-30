# 2010 Tokyo: The Two Men of the Japanese Alps
## Solution

题目可以抽象成一个最短路的模型。由于两个人必须处在所处相同的高度，用状态dis[x][y][h]来表示左边的人在第x条线段，右边的人在第y条线段，两人处于h高度时，所需走的最短路程，状态数目为100的三次方。在(x,y,h)的状态下，两人的运动可能会有如下情况：（-&gt; &lt;-）（&lt;- -&gt;）（-&gt; -&gt;）（&lt;- &lt;-）（S &lt;-）（S -&gt;）（&lt;- 
S）（-&gt; S）。其中，S表示某个人静止不动。如果某个运动合理（扩展后高度仍相等），那么求最短路的时候就可以扩展。

把山峰之间的关系（点与点之间的距离等等）预处理出来之后，使用dijkstra算法求最短路即可。