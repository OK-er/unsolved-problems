# 一分为二 2 解题思路

**题目**：[P17515 [ECUSTPC 2026 Fall] 一分为二 2](https://www.luogu.com.cn/problem/P17515)

拼接点任选，最大化"m 个不相邻选中元素的最小值"。

---

## 一、二分答案

典型的"最大化最小"问题：二分 $p$，检查是否存在拼接点 $k$，使得新数组 $c$ 中能选出 $m$ 个**互不相邻且值 $\ge p$** 的元素。

若能选 → $p$ 可行，尝试更大；否则尝试更小。

## 二、固定 p 的预处理

对固定阈值 $p$，定义：

- `preNo[k]` / `preYes[k]`：$a[1..k]$ 中最大不相邻选数，且 $a_k$ 不选 / 选（$a_k < p$ 时 `preYes[k] = -∞`，不可选）。
- `sufYes[j]` / `sufNo[j]`：$b[j..n]$ 中最大不相邻选数，且 $b_j$ 选 / 不选。

递推（从左到右 / 从右到左）：

$$\text{preNo}[k] = \max(\text{preNo}[k-1], \text{preYes}[k-1])$$
$$\text{preYes}[k] = \begin{cases} \text{preNo}[k-1] + 1, & a_k \ge p \\ -\infty, & a_k < p \end{cases}$$

后缀同理对称。

## 三、枚举拼接点 k

拼接 $c = a[1..k] + b[k+1..n]$，相邻边界为 $a_k$ 与 $b_{k+1}$（不能同时选）：

$$\text{opt}(k) = \max\bigl(\text{preYes}[k] + \text{sufNo}[k+1],\; \text{preNo}[k] + \max(\text{sufYes}[k+1], \text{sufNo}[k+1])\bigr)$$

- 第一项：$a_k$ 选、$b_{k+1}$ 不选；
- 第二项：$a_k$ 不选、$b_{k+1}$ 任意。

边界单独处理：$k=0$ 用 `max(sufYes[1], sufNo[1])`（$c=b$），$k=n$ 用 `max(preNo[n], preYes[n])`（$c=a$）。

只要存在 $k$ 使 $\text{opt}(k) \ge m$，$p$ 可行。

---

## 四、复杂度

- 单次 check：$O(n)$；
- 二分：$O(\log V)$（$V \approx 2\times10^9$，约 31 次）；
- 总：$O(n \log V)$ per test，$\sum n \le 2\times10^5$ 可过。

## 五、验证

官方 2 组样例：`5`、`-4` 逐组匹配。

## 六、易错点

1. **边界相邻约束**：拼接点 $a_k$ 与 $b_{k+1}$ 不能同选，必须分情况讨论；
2. **$a_k < p$ 时 `preYes[k] = -∞`**：不能选，避免错误转移；
3. **二分上取整**：`mid = lo + (hi - lo + 1) / 2`，找最大可行值。
