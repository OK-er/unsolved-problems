# Clean Substrings 解题思路

**题目**：[E. Clean Substrings — Codeforces Round 1123 (Div. 2)](https://codeforces.com/contest/2267/problem/E)

求二进制串 $s$ 所有子串 beauty 之和（power），并支持 $q$ 次单点翻转后实时输出。

---

## 一、beauty(t) 化简：等于断点个数的一半（向上取整）

把串 $t$ 按连续相同字符切成若干 **run**，称相邻字符不同的位置为**断点**（边界），记个数 $d(t)$。

- 操作是"翻转一个 clean 子串"。clean 子串内部必然全相同，所以它是某个 run 的一段。翻转它时：
  - 子串内部仍全相同，内部断点不变；
  - 只可能改变左右两端各一条边界。
- 即一次操作至多让断点总数 $d$ 减少 $2$；端点处操作最多减少 $1$。
- 目标 $d=0$，故最少操作数：

$$beauty(t) = \left\lceil \frac{d(t)}{2} \right\rceil$$

（每步消除至多两个断点，且构造性可达：从两端交替翻转即可。）

## 二、power(s) 的整体化简

$$power(s)=\sum_{所有子串 t}\left\lceil \frac{d(t)}{2}\right\rceil
=\frac{1}{2}\left(\sum_t d(t)+\sum_t\bigl(d(t)\bmod 2\bigr)\right)$$

分别处理两项：

### 项 1：$\sum_t d(t)$

对断点边界 $i$（$1\le i<n$，$s_i\ne s_{i+1}$），统计有多少个子串包含这条边界：左端点可选 $1..i$（共 $i$ 种），右端点可选 $i+1..n$（共 $n-i$ 种）→ 贡献 $i\cdot(n-i)$。

记

$$S=\sum_{\text{断点 }i} i\cdot(n-i)$$

### 项 2：$\sum_t (d(t)\bmod 2)$

对任意子串 $s[l..r]$，

$$d(s[l..r])=(s_l\oplus s_{l+1})+(s_{l+1}\oplus s_{l+2})+\cdots+(s_{r-1}\oplus s_r)$$

mod 2 后相邻项抵消，得到 $d\bmod 2 = s_l\oplus s_r$。即"两端字符不同的子串"计数：一个 $0$ 位置配一个 $1$ 位置的有序对子，共 $cnt_0\cdot cnt_1$ 个。

### 合并

$$\boxed{\,power(s)=\dfrac{S+cnt_0\cdot cnt_1}{2}\,}$$

---

## 三、单点翻转的 O(1) 维护

翻转 $s_{pos}$ 只影响两条边界：$(pos{-}1, pos)$ 与 $(pos, pos{+}1)$（边界外的不存在则跳过）。

- 每条边界的"是否断点"状态取反：原来是断点 → 删除贡献 $i\cdot(n-i)$；不是断点 → 新增贡献 $i\cdot(n-i)$。
- $cnt_0, cnt_1$ 相应转移（该位 0↔1）。

每修改一次 $O(1)$。初始化 $O(n)$，总复杂度 $O(n+q)$。

---

## 四、实现要点

- 答案可能很大：$i\cdot(n-i)$ 与 $cnt_0\cdot cnt_1$ 都到 $10^{10}$ 量级，须用 `long long`；
- `S + cnt0*cnt1` 恒为偶数（由定义），直接整数除法；
- 注意 $pos=1$ / $pos=n$ 时只有一条边界会变化。

## 五、复杂度

- 时间：每组 $O(n+q)$，总 $O(\sum n+\sum q)$；
- 空间：$O(n)$（断点标记数组 `pr`）。

## 六、验证

官方 4 组样例逐组输出匹配：

```
2 2
7 5 5
36 23 22 25 26
61 66 41 35 59 60
```
