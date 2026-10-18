# 2261D2 - Come Be My Friend, Don't Be So Scared (Hard Version)

**来源**：[Codeforces Round 1128 (Div. 1+2) — Problem D2](https://codeforces.com/contest/2261/problem/D2)

- 比赛：WorldQuant Round 1
- 标签：constructive algorithms, data structures, dsu, hashing, trees, two pointers
- 分数：2250（hard version）

## 题目描述

$n$ 个位置排成一行，Lord Verity 已安装了 $m$ 个区间检测器，第 $i$ 个覆盖 $[l_i, r_i]$。每个检测器报告"你是否藏在该区间内"。所有检测器同时激活。

你可以额外安装若干区间检测器。求最少需要安装多少个，使得**无论你藏在哪个位置，所有检测器的报告组合都能唯一确定位置**。同时输出一种安装方案。

## 输入格式

多组数据。每组：

- 第一行 $n, m$（$1 \le n \le 2\times10^5$, $0 \le m \le 2\times10^5$）；
- 接下来 $m$ 行，每行 $l_i, r_i$。

保证 $\sum n, \sum m \le 2\times10^5$。

## 输出格式

第一行输出 $k$（最少新增检测器数），接下来 $k$ 行输出 $[u_j, v_j]$。

## 样例

### 输入

```
7
1 0
2 0
3 0
5 2
2 2
4 4
8 7
1 2
2 3
3 4
4 5
5 6
6 7
7 8
5 2
2 3
1 5
4 2
1 2
3 4
```

### 输出

```
0
1
1 1
2
1 1
2 2
2
1 3
1 1
0
2
1 4
1 2
1
2 3
```

### 样例解释

- $n=1$：只有一个位置，天然确定。
- $n=2, m=0$：装一个单点检测器 $[1,1]$。
- $n=5, m=2$，检测器 $[2,2], [4,4]$：位置 1,3,5 签名相同（空），需要 2 个新区间区分。
