# 2269E - KiaKio and Energy Intervals

**来源**：[Codeforces Round 1124 (Div. 1+2) — Problem E](https://codeforces.com/contest/2269/problem/E)

- 题解：[Codeforces Blog entry/157140](https://codeforces.com/blog/entry/157140)

## 题目描述

给定长度 $n$ 的数组 $a$。对区间 $[l, r]$（$l < r$），定义其值：

$$\text{val}(l, r) = (a_l \& m) \oplus (a_{l+1} \& m) \oplus \dots \oplus (a_r \& m), \quad m = \max(a_l, a_{l+1}, \dots, a_r)$$

求所有区间中 $\text{val}(l, r)$ 的最大值。

## 输入格式

多组数据。每组数据第一行 $n$，第二行 $n$ 个整数 $a_i$。

## 输出格式

每组数据输出最大值。
