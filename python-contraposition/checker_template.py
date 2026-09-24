#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
算法竞赛对拍模板：Python 暴力 vs C++（或 Python 高效实现）

用法：
    python checker_template.py [轮数] [高效实现可执行文件]

示例（Windows）：
    g++ -O2 -std=c++17 -o main.exe main.cpp
    python checker_template.py 500 main.exe

核心流程：
    生成器(gen_case) -> 暴力(brute) -> 高效(solve_fast) -> 逐行比对
"""

import itertools
import random
import subprocess
import sys

# ============================================================
# 1. 数据生成器：随机生成「合法的小规模」输入，返回完整输入文本
#    注意：参数取小（暴力才跑得动）；严格满足题面约束
# ============================================================
def gen_case(rng: random.Random) -> str:
    # 示例：n 个整数数组 + 查询的通用结构，按你的题目改写
    n = rng.randint(1, 8)                    # 小规模
    arr = [rng.randint(1, 12) for _ in range(n)]
    lines = [str(n), " ".join(map(str, arr))]
    return "\n".join(lines) + "\n"

# ============================================================
# 2. 暴力求解：按题意直写，允许指数级复杂度
# ============================================================
def brute(inp: str) -> str:
    data = inp.split()
    it = iter(data)
    n = int(next(it))
    arr = [int(next(it)) for _ in range(n)]

    # ---- 在此按题意直写暴力逻辑 ----
    out = []
    for r in range(2, n + 1):
        for sub in itertools.combinations(arr, r):
            out.append(str(sub))
    # ---- 暴力逻辑结束 ----

    return "\n".join(out) + ("\n" if out else "")

# ============================================================
# 3. 高效实现：调用编译好的 C++ 可执行文件
#    （也可替换为 Python 高效实现，直接解析 inp 返回输出）
# ============================================================
def solve_fast(inp: str, exe: str) -> str:
    r = subprocess.run(
        [exe],
        input=inp,
        text=True,
        capture_output=True,
        timeout=10,            # 防止高效实现死循环挂死对拍
    )
    return r.stdout

# ============================================================
# 4. 主循环：批量随机对拍，失败即打印最小反例并退出
# ============================================================
def main() -> None:
    rounds = int(sys.argv[1]) if len(sys.argv) > 1 else 500
    exe = sys.argv[2] if len(sys.argv) > 2 else "./main"

    rng = random.Random(20240924)   # 固定种子：出错后可复现

    for i in range(rounds):
        inp = gen_case(rng)
        got_b = brute(inp).strip().splitlines()
        got_f = solve_fast(inp, exe).strip().splitlines()

        if got_b != got_f:
            print(f"[FAIL] case {i + 1}")
            print("--- input ---")
            print(inp, end="")
            print("--- brute (暴力) ---")
            print("\n".join(got_b))
            print("--- fast (高效) ---")
            print("\n".join(got_f))
            # 失败用例保存下来便于单独复现
            with open("failed_case.txt", "w", encoding="utf-8") as f:
                f.write(inp)
            sys.exit(1)

    print(f"[OK] {rounds} cases passed")

if __name__ == "__main__":
    main()
