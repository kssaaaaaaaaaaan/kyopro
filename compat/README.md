# compat/

clangd（Clang）でも GCC 専用ヘッダを静的チェックできるようにするための互換シム置き場。

`.clangd` に `-I/Users/super/kyopro/compat/` を追加してあるため、`#include <bits/stdc++.h>` や `#include <ext/pb_ds/...>` はここのファイルが優先して読まれる。

## 仕組み

各ヘッダは `#ifdef __clang__` で分岐している：

- **Clang（clangd）** → このディレクトリの Clang 互換実装を使用
- **GCC（実ビルド）** → `#include_next` で本物のシステムヘッダに転送

## シム一覧

| ヘッダ | 概要 |
|--------|------|
| `bits/stdc++.h` | `<bits/stdc++.h>` の代替 + `__int128` の `abs` / `numeric_limits` 補完 |
| `ext/pb_ds/assoc_container.hpp` | `tree`（`order_of_key` / `find_by_order`）・`cc_hash_table`・`gp_hash_table` |
| `ext/pb_ds/tree_policy.hpp` | `tree_order_statistics_node_update` の定義 |
| `ext/rope` | `rope<CharT>` / `crope` |

## 新しいシムを追加するとき

同じディレクトリ構造でファイルを作り、`#ifdef __clang__` / `#include_next` のパターンに合わせる。
