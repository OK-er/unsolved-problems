# 2261C - I Know About a Million Things

**来源**：[Codeforces Round 1128 (Div. 1+2) — Problem C](https://codeforces.com/contest/2261/problem/C)

- 比赛：WorldQuant Round 1
- 标签：games, math

## 题目描述

Moggity 和 Larpity 用一个正整数数组 $a_1, a_2, \dots, a_n$ 玩游戏，Moggity 先手，轮流操作。

每回合玩家选择一个非空位置集合，删除这些位置上的元素。操作合法当且仅当满足以下至少一条：

- 恰好删除一个元素；
- 删除元素的总和为偶数。

无法操作的玩家输（面对空数组的玩家输）。

判断先手 Moggity 有无必胜策略。

## 输入格式

多组数据。每组数据：

- 第一行 $n$（$1 \le n \le 10^6$）；
- 第二行 $n$ 个整数 $a_i$（$1 \le a_i \le 10^6$）。

保证 $\sum n \le 10^6$。

## 输出格式

先手胜输出 `Moggity`，后手胜输出 `Larpity`。

## 样例

### 输入

```
3
1
7
2
2 3
6
1000000 999999 5 4 3 2
```

### 输出

```
Moggity
Larpity
Moggity
```

### 样例解释

- [7]：先手直接删掉，后手面对空数组输。
- [2,3]：先手不能一次删两个（2+3=5 奇），只能删一个；后手删剩下的，先手面对空数组输。
