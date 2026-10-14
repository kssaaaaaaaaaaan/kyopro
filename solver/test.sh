#!/bin/bash
# main.cpp と naive.cpp の出力を比べる。
#   bash test.sh              … generate.py で作ったランダムケースで、食い違うまで繰り返す
#   bash test.sh FILE...      … 渡した入力ファイル (hands/*.txt など) を 1 つずつ流して比べる
set -u

# 入力ファイルは呼び出し元からの相対パスで渡されるので、cd する前に絶対パスにしておく
FILES=()
for f in "$@"; do
    if [ ! -f "$f" ]; then
        echo "no such file: $f" >&2
        exit 1
    fi
    FILES+=("$(cd "$(dirname "$f")" && pwd)/$(basename "$f")")
done

# 表示には呼び出し元からの相対パスを使うので、元のカレントディレクトリを渡しておく
export CALLER_PWD="$PWD"
cd "$(dirname "$0")"

ROOT="$(cd .. && pwd)"
CXX=/opt/homebrew/bin/g++
# libstdc++ を静的リンクすると、起動時の動的ロードが減って1回の実行が速くなる
CXXFLAGS=(-std=gnu++20 -O2 -static-libstdc++ -static-libgcc -I "$ROOT/ac-library" -I "$ROOT/ei1333-library")

"$CXX" "${CXXFLAGS[@]}" -o main  main.cpp  || exit 1
"$CXX" "${CXXFLAGS[@]}" -o naive naive.cpp || exit 1

# ケースごとに python3 を起動すると、その起動時間が1ケースの時間の大半を占める。
# そこで1つの Python プロセスの中で generate.py を繰り返し実行し、main と naive を呼ぶ。
exec python3 - "${FILES[@]+"${FILES[@]}"}" <<'EOF'
import io, os, subprocess, sys

def run(prog, inp):
    return subprocess.run([prog], input=inp, capture_output=True, text=True)

def check(inp, label):
    """main と naive に inp を流し、一致すれば True。食い違えば内容を表示して False"""
    r1 = run("./main", inp)
    r2 = run("./naive", inp)
    if r1.returncode == 0 and r2.returncode == 0 and r1.stdout == r2.stdout:
        return True
    # 反例を再現できるよう、入力と出力を test_result/ に残す
    os.makedirs("test_result", exist_ok=True)
    open("test_result/in.txt", "w").write(inp)
    open("test_result/out1.txt", "w").write(r1.stdout)
    open("test_result/out2.txt", "w").write(r2.stdout)
    for name, r in (("main", r1), ("naive", r2)):
        if r.returncode != 0:
            print(f"{name} crashed ({label})")
            sys.stderr.write(r.stderr)
            print(inp, end="")
            return False
    print(f"WA found ({label})")
    print("--- input");  print(inp, end="")
    print("--- main");   print(r1.stdout, end="")
    print("--- naive");  print(r2.stdout, end="")
    return False

files = sys.argv[1:]
if files:
    print("file test started")
    # 1 つ食い違っても残りは流すが、test_result/in.txt などに残るのは最後に食い違ったものになる
    failed = [f for f in files if not check(open(f).read(), os.path.relpath(f, os.environ["CALLER_PWD"]))]
    print(f"{len(files) - len(failed)}/{len(files)} files passed")
    sys.exit(1 if failed else 0)

print("random test started")
code = compile(open("generate.py").read(), "generate.py", "exec")

def generate():
    buf = io.StringIO()
    stdout, sys.stdout = sys.stdout, buf
    try:
        exec(code, {"__name__": "__main__"})
    finally:
        sys.stdout = stdout
    return buf.getvalue()

i = 0
while True:
    i += 1
    try:
        inp = generate()
    except Exception as e:
        print("generator failed:", e)
        sys.exit(1)
    if not check(inp, f"case {i}"):
        sys.exit(1)
    if i % 100 == 0:
        print(f"{i} cases passed", flush=True)
EOF
