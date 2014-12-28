# 2008 Dhaka: Puzzles of Triangles
## Summary

给出一个N × N的正方形，问有多少种方法，如图，将其分解成四个直角三角形。 

![Alt text](https://github.com/pkkj/ACM-ICPC-OJ-Code/raw/master/ACM-ICPC-Live-Archive/2008.Dhaka/4203_Img1.jpg "Image 1")
## Solution

如图，若只考虑中间的之间三角形的其中一个锐角在A，且FC&lt;CE，答案为ans，那么最终答案就是ans*8。

设：FC=b,CE=a,EB=d,FD=c，根据勾股定理和各个等量关系，能够得出：

a<sup>2</sup>/N=a-b。

题目要求所有数字都是整数，且明显，a&lt;N。那么将N分解质因数，若a<sup>2</sup> mod N = 0，那么必有：如果N=p1<sup>e1</sup>p2<sup>e2</sup>p3<sup>e3</sup>..pk<sup>ek</sup>，那么最小的a必为：

mina = p1<sup>(e1+1)/2</sup>p2<sup>(e2+1)/2</sup>p3<sup>(e3+1)/2</sup>..pk<sup>(ek+1)/2</sup>

指数之中的除法是整除。

那么mina, 2mina, 3mina...(N/mina)mina都是符合要求的。这时方案数为：ans=N/mina-1。

