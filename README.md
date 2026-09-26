# unsolved-problems · 未解之题

算法竞赛题解仓库。

每道题一个目录，目录内三份文件（题面 / 题解 / 代码分开存放）：

```
<题目目录>/
├── problem.md     # 题面（含输入输出格式、数据范围、样例、题目来源）
├── solution.md    # 解题思路（含推导、证明、复杂度分析）
└── main.cpp       # 高可读性 AC 代码（可直接提交 OJ）
```

部分题目的目录中额外附有 `learning-path.md`——以该题为最终目标、断点可验证的梯度学习路径规划书。

## 难度分层

仓库按难度将题目分为三个层次，便于按水平自取：

- **L1 · 基础**：思路直观，一两个循环 + 简单观察即可解决，适合作为入门训练；
- **L2 · 提高**：需要建模或 DP/筛法等常规技巧，是竞赛中档题的典型构成；
- **L3 · 困难**：多个知识点复合（组合恒等式 + 数论 + 递推），需系统学习前置知识才能攻克。

### L1 · 基础

| 题目 | 目录 | 题面 | 题解 | AC 代码 | 来源 |
|---|---|---|---|---|---|
| 新鲜子数组（Fresh Subarrays） | `fresh-subarrays/` | [problem.md](fresh-subarrays/problem.md) | [solution.md](fresh-subarrays/solution.md) | [main.cpp](fresh-subarrays/main.cpp) | [牛客周赛 Round 162](https://ac.nowcoder.com/acm/contest/140489) |
| Kaky 撞障碍物（Kaky Obstacles） | `kaky-obstacles/` | [problem.md](kaky-obstacles/problem.md) | [solution.md](kaky-obstacles/solution.md) | [main.cpp](kaky-obstacles/main.cpp) | 题面截图（来源未显示） |

### L2 · 提高

| 题目 | 目录 | 题面 | 题解 | AC 代码 | 来源 |
|---|---|---|---|---|---|
| 删除连通点集（Delete Connected Set） | `delete-to-monochrome/` | [problem.md](delete-to-monochrome/problem.md) | [solution.md](delete-to-monochrome/solution.md) | [main.cpp](delete-to-monochrome/main.cpp) | [牛客周赛 Round 162](https://ac.nowcoder.com/acm/contest/140489) |
| Falling Concrete | `falling-concrete/` | [problem.md](falling-concrete/problem.md) | [solution.md](falling-concrete/solution.md) | [main.cpp](falling-concrete/main.cpp) | [Codeforces 2266D](https://codeforces.com/contest/2266/problem/D) |
| Prime Destruction | `prime-destruction/` | [problem.md](prime-destruction/problem.md) | [solution.md](prime-destruction/solution.md) | [main.cpp](prime-destruction/main.cpp) | Codeforces E |
| Equal Shopping | `equal-shopping/` | [problem.md](equal-shopping/problem.md) | [solution.md](equal-shopping/solution.md) | [main.cpp](equal-shopping/main.cpp) | [AtCoder WDC 0163 Beta](https://atcoder.jp/contests/awc0163/tasks/awc0163_d) |
| 飞行路线（Flight Route） | `flight-route/` | [problem.md](flight-route/problem.md) | [solution.md](flight-route/solution.md) | [main.cpp](flight-route/main.cpp) | [洛谷 P4568](https://www.luogu.com.cn/problem/P4568) |
| Backrooms Hill | `backrooms-hill/` | [problem.md](backrooms-hill/problem.md) | [solution.md](backrooms-hill/solution.md) | [main.cpp](backrooms-hill/main.cpp) | [Codeforces 2267D](https://codeforces.com/contest/2267/problem/D) |

### L3 · 困难

| 题目 | 目录 | 题面 | 题解 | AC 代码 | 来源 |
|---|---|---|---|---|---|
| Start to the End | `start-to-the-end/` | [problem.md](start-to-the-end/problem.md) | [solution.md](start-to-the-end/solution.md) | [main.cpp](start-to-the-end/main.cpp) | [2026 牛客多校 Day 9](https://ac.nowcoder.com/) |
| Brackets | `brackets/` | [problem.md](brackets/problem.md) | [solution.md](brackets/solution.md) | [main.cpp](brackets/main.cpp) | [2026 牛客暑期多校训练营10](https://ac.nowcoder.com/acm/contest/133885) |

> `start-to-the-end/` 目录额外含 `learning-path.md`——以该题为最终目标、断点可验证的梯度学习路径规划书。

## 工具 · 对拍技巧

| 内容 | 路径 | 说明 |
|---|---|---|
| Python 对拍能力与技巧总结 | [`python-contraposition/README.md`](python-contraposition/README.md) | 框架、生成器设计、交互、调试流程、实战案例 |
| 可复用对拍模板 | [`python-contraposition/checker_template.py`](python-contraposition/checker_template.py) | 生成器 + 暴力 + subprocess 调 C++ + 批量比对，改两处即可用 |
