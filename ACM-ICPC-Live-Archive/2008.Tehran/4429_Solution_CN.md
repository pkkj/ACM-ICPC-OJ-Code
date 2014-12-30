# 2008 Tehran: Hurry Plotter
## Summary

给出N(N<=1000)个需要绘制的平行于X轴的线段，知道其坐标，以(Y,X1,X2)表示。有一绘图仪，从Y=0位置开始绘制这些线段。对于同一个Y，绘图仪可以从X=x1到X=x2，平移时耗费时间|x2-x1|，绘制线段则耗费双倍时间2|x2-x1|。但是，在垂直方向上，绘图仪只能从y1移动到y2，y1<y2，且此时X必须=0。线段的绘制必须是完整的，不能只绘制一半。现问：绘图仪在规定的之间T内最多能绘制多少条线段。

## Solution

使用动态规划可以解决这个问题。

设DP状态为：dp[i][j]，表示绘制到第i个线段（这个线段必须绘制），绘制了j个线段，所需要的最少时间。那么dp[i][j] = min(dp[k][j-1] + dis(segment[i], segment[k]) + time to draw segment[i]。dis表示两个线段的“距离”，分情况讨论计算即可。

最后统计所有时间小于等于T的方案取出最优的即可。