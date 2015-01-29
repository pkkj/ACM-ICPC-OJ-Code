# 2010 Hangzhou: Rotational Painting
## Solution

按以下步骤解决该题即可：

1. 求出给出的多边形的重心。可以使用三角剖分的方法求任意多边形的重心。求法：

根据多边形重心的定义,可以对其进行三角剖分,计算每个三角形的面积以及重心.多边形的重心就是所有三角形的重心对 面积的加权平均数,也就是说: 
<pre>
center.x = (cen[0].x * area[0] + cen[1].x * area[1] ..... + cen[n].x * area[n]) / totalarea
center.y = (cen[0].y * area[0] + cen[1].y * area[1] ..... + cen[n].y * area[n]) / totalarea
</pre>

cen[i]代表第i个三角形的重心,三角形的重心就是: 
<pre>
center_of_tri.x=(p1.x+p2.x+p3.x)/3.0
center_of_tri.y=(p1.y+p2.y+p3.y)/3.0
</pre>

2. 对给出的点求凸包。因为放的时候，朝地面的方向的那条边必定在点集的凸包的一条边上。
3. 枚举凸包上的每一条边，看看把这条边放在桌上，能不能放稳。放稳的前提很容易想到：重心与桌子的垂足落在凸包与桌子相邻的那条边的内部（端点也不行），使用点积既可以进行判断。 
