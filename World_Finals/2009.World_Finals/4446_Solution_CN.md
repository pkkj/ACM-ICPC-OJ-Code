# 2009 World Final: My Bad

## Solution
由于题目规模很小，因此可以枚举每个电路门的错误状态，然后使用拓扑序正向搜一次，或记忆化搜索反向递归一次，求出所有输入的相应输出是否和题目给出的一致。

注意题目的描述，如果在没有任何电路门错误的情况下能够得到所有的正确输出，那么答案是No faults detected。对于每个电路门要记录其可能的错误数目。当且仅当有一个电路门有一种错误时，输出详细的错误信息。否则都是Unable to totally classify the failure。 
