# 2010 Tokyo: Find the Multiples

## Solution

先求出序列A。设A的组成为a<sub>1</sub>a<sub>2</sub>a<sub>3</sub>...a<sub>n</sub>，由a<sub>k</sub>a<sub>k+1</sub>...a<sub>n</sub>组成的数字为S<sub>k</sub>。如果S<sub>a</sub> mod Q = S<sub>b</sub> mod Q，且a&lt;b，那么有(S<sub>a</sub>-S<sub>b</sub>) mod Q=0，而S<sub>a</sub>-S<sub>b</sub>也就是A序列中第a位与第b位数字之间组成的数，也就是题目要统计的对象。

S<sub>k</sub>可以边乘十，边累加、边求余进行计算，每次都检查S<sub>k</sub> mod Q，看看前面该余数在前面出现了多少次。如果S<sub>k</sub> mod Q=0，那么答案就加上该余数在前面出现的次数；如果S<sub>k</sub> mod Q≠0，那么答案就加上该余数在前面出现的次数减一。注意，如果a<sub>k</sub>为0，就不需要累加，因为题目不需要统计以0开头的数字。这个统计过程可以使用一个类似map的结构辅助。

对于Q为2或5需要特判。因为这两个素数比较特殊。如2，一旦当前数位上出现2的倍数，那么不管a的前面是什么数字，都可与该数位构成2的倍数。5也是如此。因此这两个数字需要特殊处理。

