# 2009 Shanghai: Compressed String

## Solution

字符串展开后的规模十分巨大，因此是不可能展开后再进行比较。下面程序使用的方法是先二分一个答案X，然后再利用Hash来比较两个字符串的前X个 字符是否一样。

下面的代码使用一种等差数列的方法进行Hash，边递归边进行Hash。 

#### Thank
3xian
