# 2010 Tokyo: Awkward Lights

## Solution
把每个位置的开关的状态都看成一个变量x<sub>i</sub>，x<sub>i</sub>=1或x<sub>i</sub>=0分别表示触动之或不触动，那么可以把问题抽象成一个方程组。设第k个灯，其当前状态为st，st=1表示灯亮，st=0表示灯灭，此灯受到开关x<sub>k1</sub>，x<sub>k2</sub>，...，x<sub>kn</sub>的影响，那么有方程：

(x<sub>k1</sub>+x<sub>k2</sub>+...+x<sub>kn</sub>) mod 2 = st

各个等式联立后，得到一个对2的同余方程组，可以使用高斯消元的方法解决。消元过程中的不少运算可以使用位运算代替。
