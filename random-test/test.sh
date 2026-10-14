#!/bin/bash
# main.cpp と naive.cpp の出力が食い違う入力を、generate.py で作ったランダムケースから探す。
#   bash test.sh
set -u
cd "$(dirname "$0")"

ROOT="$(cd .. && pwd)"
CXX=/opt/homebrew/bin/g++
# ライブラリのパスに空白とアポストロフィが含まれるので、配列で渡す
# libstdc++ を静的リンクすると、起動時の動的ロードが減って1回の実行が速くなる
CXXFLAGS=(-std=gnu++20 -O2 -static-libstdc++ -static-libgcc -I "$ROOT/ac-library" -I "$ROOT/Luzhiled's Library-edited")

"$CXX" "${CXXFLAGS[@]}" -o main  main.cpp  || exit 1
"$CXX" "${CXXFLAGS[@]}" -o naive naive.cpp || exit 1

echo "random test started"
# ケースごとに python3 を起動すると、その起動時間が1ケースの時間の大半を占める。
# そこで1つの Python プロセスの中で generate.py を繰り返し実行し、main と naive を呼ぶ。
exec python3 - <<'EOF'
import io, subprocess, sys

code = compile(open("generate.py").read(), "generate.py", "exec")

def generate():
    buf = io.StringIO()
    stdout, sys.stdout = sys.stdout, buf
    try:
        exec(code, {"__name__": "__main__"})
    finally:
        sys.stdout = stdout
    return buf.getvalue()

def run(prog, inp):
    return subprocess.run([prog], input=inp, capture_output=True, text=True)

i = 0
while True:
    i += 1
    try:
        inp = generate()
    except Exception as e:
        print("generator failed:", e)
        sys.exit(1)
    r1 = run("./main", inp)
    r2 = run("./naive", inp)
    if r1.returncode != 0 or r2.returncode != 0 or r1.stdout != r2.stdout:
        # 反例を再現できるよう、入力と出力をファイルに残す
        open("in.txt", "w").write(inp)
        open("out1.txt", "w").write(r1.stdout)
        open("out2.txt", "w").write(r2.stdout)
        for name, r in (("main", r1), ("naive", r2)):
            if r.returncode != 0:
                print(f"{name} crashed (case {i})")
                sys.stderr.write(r.stderr)
                print(inp, end="")
                sys.exit(1)
        print(f"WA found (case {i})")
        print("--- input");  print(inp, end="")
        print("--- main");   print(r1.stdout, end="")
        print("--- naive");  print(r2.stdout, end="")
        sys.exit(1)
    if i % 100 == 0:
        print(f"{i} cases passed", flush=True)
EOF
