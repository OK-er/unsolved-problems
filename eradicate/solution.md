# 根除 解题思路

**题目**：[P17517 [ECUSTPC 2026 Fall] 根除](https://www.luogu.com.cn/problem/P17517)

求平方自由部分函数 $f(n)$ 的区间和，$r \le 10^{12}$。

---

## 一、按表示法分类

$n = a b^2$（$a$ 平方自由）时 $f(n) = a$。对固定 $a$（平方自由），$b$ 可取 $1, 2, \dots, \lfloor\sqrt{N/a}\rfloor$。

前缀和 $S(N) = \sum_{n=1}^N f(n)$ 可按 $b$ 重新分组：

$$S(N) = \sum_{b=1}^{\lfloor\sqrt N\rfloor} \sum_{\substack{a \le N/b^2 \\ a \text{ 平方自由}}} a
       = \sum_{b=1}^{\lfloor\sqrt N\rfloor} G\!\left(\left\lfloor\frac{N}{b^2}\right\rfloor\right)$$

其中 $G(M) = \sum_{a \le M,\, a \text{ 平方自由}} a$。

## 二、莫比乌斯反演求 G(M)

利用指示函数 $[a \text{ 平方自由}] = \sum_{d^2 \mid a} \mu(d)$：

$$G(M) = \sum_{a \le M} a \sum_{d^2 \mid a} \mu(d)
       = \sum_{d \le \sqrt M} \mu(d) \sum_{\substack{a \le M \\ d^2 \mid a}} a$$

令 $a = d^2 k$，内层和为 $d^2 \sum_{k=1}^{\lfloor M/d^2 \rfloor} k = d^2 \cdot T(\lfloor M/d^2 \rfloor)$，其中 $T(x) = x(x+1)/2$。

$$G(M) = \sum_{d \le \sqrt M} \mu(d)\, d^2 \cdot T\!\left(\left\lfloor\frac{M}{d^2}\right\rfloor\right)$$

线性筛预处理 $\mu(d)$ 到 $10^6$（$\sqrt{10^{12}}$）。

## 三、分块 + 缓存

- $b$ 按 $\lfloor N/b^2 \rfloor$ 分块（相同值合并一段），每块贡献 `块长 * G(M)`；
- $G(M)$ 用 `unordered_map` 缓存，多组询问共享相同 $M$ 时只算一次；
- $T(x)$ 中 $x$ 可能到 $10^{12}$，先取模再乘。

---

## 四、复杂度

- 线性筛 $O(10^6)$；
- 单次询问 $S(N)$：分块段数 $O(N^{1/3})$，每段 $G(M)$ 调用带缓存；
- 所有询问合计约 $O(\sqrt N \log N)$ 量级，$10^{12}$ 可过。

## 五、验证

官方 4 组样例：`3, 38, 66, 651260790` 逐组匹配（含 $N=10^8$ 大样例）。

## 六、易错点

1. **$T(x) = x(x+1)/2$ 取模**：$x$ 到 $10^{12}$，必须先 `% MOD` 再乘；
2. **分块边界**：`maxb = floor(sqrt(N/M))` 要校正浮点误差（`while` 循环上下调整）；
3. **$G(M)$ 必须缓存**：否则多组询问重复计算超时；
4. **$\mu(d)$ 为 0 时跳过**：含平方因子的 $d$ 贡献为 0，省一半循环。
