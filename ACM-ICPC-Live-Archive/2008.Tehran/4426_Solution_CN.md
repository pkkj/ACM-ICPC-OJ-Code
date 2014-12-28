# 2008 Tehran: Blast the Enemy!
## Summary

给出一个有n(n<=100)个点的简单多边形，求该多边形的重心。
## Solution

根据多边形重心的定义，可以对其进行三角剖分，计算每个三角形的面积以及重心。多边形的重心就是所有三角形的重心对面积的加权平均数，也就是说：
<pre>
center.x = (cen[0].x * area[0] + cen[1].x * area[1] ..... + cen[n].x * area[n]) / totalarea
center.y = (cen[0].y * area[0] + cen[1].y * area[1] ..... + cen[n].y * area[n]) / totalarea
</pre>
cen[i]代表第i个三角形的重心，三角形的重心就是：

<pre>
center_of_tri.x=(p1.x+p2.x+p3.x)/3.0
center_of_tri.y=(p1.y+p2.y+p3.y)/3.0
</pre>
area[i]就是第i个三角形的面积。totalarea就是多边形的总面积。

三角剖分的技巧是：三角形的一个点是原点，然后枚举多边形的另外两个相邻的点，构成三角形。所有的面积均为有向面积，这样可以无论点是顺时 针还是逆时针给出，都无需特殊处理，且运算简单。 
