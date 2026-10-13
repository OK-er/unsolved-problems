# What a SauSaGe! It's All Meat 解题思路

**题目**：[2269D — Codeforces Round 1124](https://codeforces.com/contest/2269/problem/D)

操作 mask 异或相邻两元素，问最多多少元素能变成 All-Meat（偶 popcount 4-bit 数）。

---

## 一、不变量：popcount 奇偶性

所有操作 mask $3,6,12,9,15$ 的二进制表示：

| mask | 二进制 | popcount |
|---|---|---|
| 3 | 0011 | 2（偶） |
| 6 | 0110 | 2（偶） |
| 9 | 1001 | 2（偶） |
| 12 | 1100 | 2（偶） |
| 15 | 1111 | 4（偶） |

**全部是偶 popcount**。异或一个偶 popcount 数不会改变原数 popcount 的奇偶性。

而 All-Meat 集合 $\{0,3,6,9,12,15\}$ 全是偶 popcount → **奇 popcount 的元素永远无法变成 All-Meat**。

上界：$\#\{i \mid \text{popcount}(a_i) \text{ 为偶}\}$。

## 二、上界可达

**关键观察 1**：mask 可施加到任意两元素（不限于相邻）。

想对 $a_i, a_j$（$i<j$）施加 mask，就对相邻对 $(i,i+1),(i+1,i+2),\dots,(j-1,j)$ 依次施加同一 mask。中间元素被异或两次抵消，只有 $a_i, a_j$ 被异或一次。

**关键观察 2**：任意偶 popcount 的 4-bit 数都能作为复合 mask。

偶 popcount 4-bit 数集合 $E = \{0,3,5,6,9,10,12,15\}$。其中 5 和 10 不是单步 mask，但：

$$5 = 3 \oplus 6,\quad 10 = 3 \oplus 9$$

故任意偶 popcount mask 都可合成。

**构造**：

- **Case 1：存在奇 popcount 元素**。选它作缓冲。对每个偶 popcount 元素 $a_i$，把 $a_i$ 与缓冲同时异或 $a_i$（$a_i$ 是偶 popcount，合法），则 $a_i \oplus a_i = 0$，变成 All-Meat；缓冲仍奇 popcount（只被偶 mask 作用）。
- **Case 2：全是偶 popcount**。以 $a_1$ 为缓冲，把 $a_1$ 与每个 $a_i$（$i\ge2$）同时异或 $a_i$，把 $a_i$ 清零。数组变 $[x,0,0,\dots,0]$，$x = a_1\oplus a_2\oplus\cdots\oplus a_n$。$x$ 必偶 popcount，仅可能是 5 或 10，再对前两个元素异或 3 修正（$5\to6$ 同时 $0\to3$，$10\to9$ 同时 $0\to3$），全部 All-Meat。

综上上界恒可达。

## 三、答案

$$\text{ans} = \#\{i \mid \text{popcount}(a_i) \text{ 为偶}\}$$

更新时删旧贡献、加新贡献，$O(1)$。

---

## 四、复杂度

- 初始处理 $O(n)$；
- 每次更新 $O(1)$；
- 总 $O(n+q)$。

## 五、易错点

1. **奇偶性不变是核心**：mask 全偶 popcount，奇 popcount 元素是"死元素"，不能贡献；
2. **mask 可跨元素施加**：相邻传递让中间元素抵消，等价于任意对操作；
3. **5、10 需复合 mask**：不是单步 mask，但可由 3⊕6、3⊕9 合成。
