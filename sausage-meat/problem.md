# 2269D - What a SauSaGe! It's All Meat

**来源**：[Codeforces Round 1124 (Div. 1+2) — Problem D](https://codeforces.com/contest/2269/problem/D)

- 题解：[Codeforces Blog entry/157140](https://codeforces.com/blog/entry/157140)

## 题目描述

给定长度为 $n$ 的数组 $a_i$（$0 \le a_i \le 15$，即 4 位二进制数）。

可执行任意次操作：选择相邻的 $i$，同时把 $a_i$ 与 $a_{i+1}$ 异或上 $3^k$（$k=0,1,2,3,4$），即 mask 只能是

$$3,\ 6,\ 12,\ 9,\ 15$$

一个数被称为 **All-Meat** 当且仅当它属于集合 $\{0,3,6,9,12,15\}$。

问经过任意次操作后，最多能让多少个元素变成 All-Meat？

附带 $q$ 次单点更新（把第 $p$ 个元素改成 $x$），每次更新后输出答案。

## 输入格式

多组数据。每组数据：

- 第一行 $n, q$；
- 第二行 $n$ 个整数 $a_i$；
- 接下来 $q$ 行，每行 $p, x$。

## 输出格式

初始答案 + 每次更新后的答案。
