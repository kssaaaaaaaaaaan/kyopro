---
title: Makefile (ビルドと提出と検証)
documentation_of: //Makefile
---

リポジトリ直下の `Makefile` は、競技プログラミングで繰り返す 3 つの作業をまとめたものである。
コンパイルと、提出用の 1 ファイル化と、Library Checker での検証である。

## 変数

対象を切り替えるのは次の 3 つである。

- **SRC**：対象のソースファイル。既定は `main.cpp`。
- **OUT**：`make submit` の出力先。既定は `SRC` の拡張子を `.submit.cpp` に替えたもの。
- **T**：`make verify` で 1 つだけ実行したいテストの名前。既定は空で、その場合は全部を実行する。

コンパイラと include パスは次の 3 つで決まっており、普段は触らない。

- **CXX**：`g++`
- **ACL**：`ac-library`
- **LIB**：`ei1333-library`（次節を参照）

`CXXFLAGS` は `-std=gnu++20 -O2 -Wall -Wextra -Wno-sign-compare` に、`ACL` と `LIB` の include パスを足したものである。
`-Wno-sign-compare` を入れているのは、FPS が `int` と `size_t` を比べる箇所を持っており、そこで警告が出続けるからである。

## ライブラリ

`ei1333-library` は、ei1333/library（Luzhiled's Library）を無改変のまま git submodule として置いたものである。
参照しているのはコミット `dca071d33d8dbfd001e450a109c55eb6c38c2ee8`（2026-08-23）である。
更新するときは `git -C ei1333-library pull` のあと `git add ei1333-library` してコミットし、参照するコミットを進める。
その際は、各 .cpp の先頭にある ei1333/library の URL のコミットハッシュも書き換える。
新しい環境で clone するときは `git clone --recursive` を使うか、clone 後に `git submodule update --init` を実行する。
使い方の説明は本家の `docs/` にある。

modint は本家のものではなく `atcoder::modint998244353` を渡す。
本家の NTT が modint に求めるのは `mod()` と `pow()` と比較演算だけで、ACL の modint はどれも持っている。

FPS は NTT 向けの `math/fps/formal-power-series-friendly-ntt.hpp` を使う。
素朴版の `math/fps/formal-power-series.hpp` より `inv` と `exp` が速く、`pow` で 2.5 倍前後の差が出る。
どちらも `FPS<Mint>` という別名を定義している。

使うときの注意が 2 つある。

- **exp の長さ**：`f.exp(deg)` に `f` の長さより大きい `deg` を渡すと、範囲外アクセスになる。先に `f.resize(deg)` してから `f.exp()` を呼ぶ。`log` と `pow` の中の呼び出しは長さが揃っているので問題ない。
- **sqrt に渡す平方根**：本家の `math/combinatorics/mod-sqrt.hpp` の `mod_sqrt` は整数を受け取るので、ラムダで包んで渡す。解がないときは `-1` を返すが、`sqrt` が二乗して確かめるのでそのまま渡してよい。

```cpp
auto get_sqrt = [](mint x) {
  return mint(mod_sqrt<long long>(x.val(), mint::mod()));
};
auto g = f.sqrt(n, get_sqrt);
```

## ターゲット

### build

`SRC` をコンパイルして、拡張子を落とした名前の実行ファイルを同じディレクトリに作る。
引数なしの `make` はこれを実行する。

```
make                          # main.cpp → ./main
make build SRC=ABC/A.cpp      # ABC/A.cpp → ABC/A
```

出力先が `ABC/A` になるのは、`$(basename ABC/A.cpp)` が `ABC/A` に展開されるからである。

### submit

`SRC` を `oj-bundle` に通し、`LIB` のヘッダを展開した 1 ファイルを `OUT` に書き出す。

```
make submit SRC=ABC/A.cpp     # → ABC/A.submit.cpp
make submit                   # → main.submit.cpp
make submit SRC=ABC/A.cpp OUT=/tmp/x.cpp
```

展開は二段で行う。
まず `oj-bundle -I "$(LIB)"` で本家のヘッダを展開する。
`oj-bundle` は `#include <...>` を展開しないので、`#include <atcoder/...>` はこの段階では残る。
次に、その出力を ACL 同梱の `expander.py` に通して ACL を展開する。
出力は ACL を含まない 1 ファイルになるので、Codeforces のように ACL が入っていないジャッジにもそのまま提出できる。

出力には `#line` 行が挟まる。
提出には影響しないが、コンパイルエラーの行番号が元ファイルの番号で報告されるようになる。

### verify

`verify/` に移ってから `oj-verify run` を実行する。
`T` を渡すとそのテストだけを実行する。

```
make verify
make verify T=inv_of_formal_power_series
```

`verify/` に移るのは、`oj-verify` がカレントディレクトリ以下の `*.test.cpp` をすべて拾うからである。
リポジトリ直下で実行すると、`ei1333-library` に入っている本家のテストまで実行してしまう。
`verify/test/` のテストは、本家のヘッダに ACL の modint を渡す使い方を確かめるものである。

### clean

`OUT` と `build` が作った実行ファイルを消す。
`SRC` を渡さなければ `main.cpp` に対応するものが対象になる。

```
make clean SRC=ABC/A.cpp      # ABC/A.submit.cpp と ABC/A を消す
```

## VSCode のタスクとの関係

ctrl+s に割り当てられている `SubmitCode` タスクは、編集中のファイルをそのまま `acc submit` に渡す。
ライブラリを使った回はこれでは通らない。
AtCoder 側に `math/fps/formal-power-series-friendly-ntt.hpp` は無く、コンパイルが通らないからである。
`make submit` で展開してから、`.submit.cpp` のほうを提出する。

1 キーにまとめるなら、`tasks.json` に次のタスクを足して ctrl+s を割り当て直す形になる。

```json
{
    "label": "BundleAndSubmit",
    "type": "shell",
    "command": "cd ${workspaceFolder} && make submit SRC=${relativeFile} && cd ${fileDirname} && acc submit ${fileBasenameNoExtension}.submit.cpp -- -l 4003"
}
```

`acc submit` に `A.cpp` 以外の名前を渡す部分は手元で確かめていない。
割り当てる前に、一度手で `acc submit A.submit.cpp -- -l 4003` を試すほうが安全である。

## 前提になるコマンド

`make submit` は `oj-bundle` を、`make verify` は `oj-verify` を使う。
どちらも online-judge-verify-helper に入っている。

```
pipx install online-judge-verify-helper
pipx inject online-judge-verify-helper "setuptools<81" --force
```

2 行目が要るのは、`oj-verify` が `pkg_resources` を使っており、setuptools 81 以降では起動しないからである。
