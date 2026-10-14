# generate.py でテストケースを作る

generate.py は、入力を1ケース分だけ標準出力に書き出すスクリプトである。
`bash test.sh` を引数なしで実行すると、test.sh はこれを毎回呼び出し、出力を main と naive に渡す。
食い違いが見つかったときは、入力を test_result/in.txt に、main と naive の出力を test_result/out1.txt と test_result/out2.txt に残すので、シードを固定しなくても再現できる。

## 基本の形

```python
import random

n = random.randint(1, 5)
a = [random.randint(1, 10) for _ in range(n)]
print(n)
print(*a)
```

`random.randint(l, r)` は l 以上 r 以下の整数を返す（両端を含む）。
`print(*a)` はリストの要素を空白区切りで1行に出力する。

## 制約の決め方

制約は、問題文の値ではなく小さい値にする。
N を 1 から 5 程度、値を 1 から 10 程度に抑えると、N = 1 や値がすべて等しい入力のような境界がたびたび出るので、境界で起きるバグを踏みやすい。
見つかった反例も小さくなり、手で追える。
naive が全探索の場合は、小さくしないと1ケースが遅くなり、回せるケース数が減る。

一方で、生成する入力は問題の制約を必ず満たすようにする。
制約外の入力では main と naive の出力が食い違っても正しい場合があり、偽の反例になる。

## 配列

用途に応じて次のように作り分ける。

```python
import random

n = random.randint(1, 5)

a = [random.randint(1, 10) for _ in range(n)]      # 重複あり
b = random.sample(range(1, 11), n)                 # 重複なし（範囲の大きさ >= n が必要）
c = sorted(random.randint(1, 10) for _ in range(n))  # 昇順
d = random.choices([0, 1], k=n)                    # 値の種類を絞る
e = [random.randint(-5, 5) for _ in range(n)]      # 負の値を含む

print(n)
print(*a)
```

値の種類を 2、3 個に絞ると、等しい値が並ぶ入力が増える。
同じ値の扱い（`<` と `<=` の取り違えなど）のバグを探すときに効く。

## 順列

1 から N の順列は、リストをシャッフルして作る。

```python
import random

n = random.randint(1, 6)
p = list(range(1, n + 1))
random.shuffle(p)
print(n)
print(*p)
```

0 始まりの順列が欲しい場合は `range(n)` にする。

## 文字列

```python
import random

n = random.randint(1, 8)
s = ''.join(random.choices('ab', k=n))
print(n)
print(s)
```

使う文字を 2、3 種類に絞ると、回文や繰り返しのような一致の多い文字列が出やすくなる。
英小文字全体を使うなら `string.ascii_lowercase` を渡す。

## グリッド

```python
import random

h = random.randint(1, 4)
w = random.randint(1, 4)
print(h, w)
for _ in range(h):
    print(''.join(random.choices('.#', weights=[3, 1], k=w)))
```

`weights` で `.` と `#` の出やすさを変えられる。
壁が多すぎると到達できない入力ばかりになるので、通路を多めにしておく。
スタートやゴールのマスが通路でなければならない問題では、出力前にそのマスを `.` で上書きする。

## 木

頂点 2 から N について、それより番号の小さい頂点から親を1つ選ぶと、必ず木になる。
ただしこのままだと頂点 1 がいつも根の位置に来て、辺も「親の番号 < 子の番号」の向きに偏る。
そこで頂点番号をシャッフルし、辺の順番と向きも混ぜる。

```python
import random

n = random.randint(1, 6)
perm = list(range(1, n + 1))
random.shuffle(perm)

edges = []
for i in range(1, n):
    j = random.randint(0, i - 1)
    u, v = perm[i], perm[j]
    if random.random() < 0.5:
        u, v = v, u
    edges.append((u, v))
random.shuffle(edges)

print(n)
for u, v in edges:
    print(u, v)
```

この方法で作る木は、全種類の木から一様に選んだものではなく、浅い木に偏る[^tree]。
深さが効く問題（再帰の深さや、パス上の処理など）では、親を `i - 1` に固定した直線の木を一定の確率で混ぜる。

[^tree]: 一様な木を作るには Prüfer 列を使う方法がある。小さい N のランダムテストでは、上の方法で足りることが多い。

## 無向グラフ

多重辺と自己ループのない**単純グラフ**は、頂点のペアを全部列挙し、そこから M 本を選んで作る。

```python
import random

n = random.randint(2, 5)
pairs = [(u, v) for u in range(1, n + 1) for v in range(u + 1, n + 1)]
m = random.randint(1, len(pairs))
edges = random.sample(pairs, m)

print(n, m)
for u, v in edges:
    if random.random() < 0.5:
        u, v = v, u
    print(u, v)
```

多重辺や自己ループを許す問題では、ペアを列挙せず `random.randint(1, n)` を2回呼んで端点を選べばよい。

## 連結グラフ

問題が連結を保証している場合は、先に木を作り、残りのペアから辺を足す。

```python
import random

n = random.randint(2, 5)
perm = list(range(1, n + 1))
random.shuffle(perm)
tree = set()
for i in range(1, n):
    u, v = perm[i], perm[random.randint(0, i - 1)]
    tree.add((min(u, v), max(u, v)))

rest = [(u, v) for u in range(1, n + 1) for v in range(u + 1, n + 1) if (u, v) not in tree]
extra = random.sample(rest, random.randint(0, len(rest)))
edges = list(tree) + extra
random.shuffle(edges)

print(n, len(edges))
for u, v in edges:
    print(u, v)
```

## 有向グラフと DAG

有向グラフでは、順序つきのペア `(u, v)`（`u != v`）から選ぶ。
DAG が必要な場合は、ランダムなトポロジカル順序を先に決め、その順序で前から後ろへ向かう辺だけを使う。

```python
import random

n = random.randint(2, 5)
order = list(range(1, n + 1))
random.shuffle(order)
pairs = [(order[i], order[j]) for i in range(n) for j in range(i + 1, n)]
m = random.randint(1, len(pairs))
edges = random.sample(pairs, m)

print(n, m)
for u, v in edges:
    print(u, v)
```

順序をシャッフルしないと、辺がすべて「小さい番号から大きい番号へ」向き、トポロジカルソートを間違えていても通ってしまう可能性がある。

## 重み

辺や頂点に重みがある場合は、出力のときに値を足すだけでよい。

```python
w = random.randint(1, 10)
print(u, v, w)
```

重みの範囲を狭くすると、同じ長さの経路が複数できやすくなる。
最短経路の同点の扱いを確かめたいときに使える。

## クエリ

クエリの種類をランダムに選び、種類ごとに引数を作る。
区間 `[l, r]` は、2つの値を選んでソートする。

```python
import random

n = random.randint(1, 5)
q = random.randint(1, 5)
print(n, q)
print(*[random.randint(1, 10) for _ in range(n)])
for _ in range(q):
    if random.randint(0, 1) == 0:
        i = random.randint(1, n)
        x = random.randint(1, 10)
        print(1, i, x)
    else:
        l, r = sorted([random.randint(1, n), random.randint(1, n)])
        print(2, l, r)
```

`random.sample(range(1, n + 1), 2)` で選ぶと必ず `l < r` になり、`l == r` の区間が出なくなる。
問題が `l <= r` を許すなら、上のように独立に2回選ぶ。

## 複数テストケース

Codeforces のように先頭でテストケース数 T を読む形式では、1ケース分を作る関数を書いて T 回呼ぶ。

```python
import random

def case():
    n = random.randint(1, 5)
    a = [random.randint(1, 10) for _ in range(n)]
    return f"{n}\n{' '.join(map(str, a))}"

t = random.randint(1, 5)
print(t)
for _ in range(t):
    print(case())
```

1ファイルに複数ケースを入れると、プログラムの起動回数あたりに試せるケースが増える。
ただし反例が見つかったときは、どのケースで食い違ったかを test_result/in.txt から探す手間が増える。

## 手で作った入力で比べる

generate.py では出にくい入力（最大ケースや、境界の値を並べたものなど）は、ファイルに書いて test.sh に渡す。
手で書く入力は hands/ に置く（hands/hand.txt を用意してある）。

```
bash test.sh hands/hand.txt
bash test.sh hands/*.txt
```

ファイルを渡すと、generate.py は使わず、各ファイルを main と naive に流して出力を比べる。
1 つが食い違っても残りのファイルは流し、最後に一致した数を表示する。
1 つでも食い違えば終了コードは 1 になる。
test_result/ の in.txt、out1.txt、out2.txt に残るのは、最後に食い違ったファイルのものである。
パスは test.sh を呼び出したディレクトリからの相対パスで渡せる。

## test.sh で比べられない問題

test.sh は main と naive の出力を文字列として比べるので、正解が一意に決まる問題にしか使えない。
「条件を満たすものを1つ出力せよ」のように複数の正解がある問題では、出力が正しいかを判定するスクリプトを別に書き、test.sh の比較の代わりに呼ぶ必要がある。
小数を出力する問題も、誤差の範囲で一致していれば正解なので、同様に判定用のスクリプトが要る。
