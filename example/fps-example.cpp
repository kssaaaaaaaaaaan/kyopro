// https://github.com/kssaaaaaaaaaaan/kyopro
// https://github.com/ei1333/library/tree/dca071d33d8dbfd001e450a109c55eb6c38c2ee8
// FPS の使い方の例。
//   make build  SRC=example/fps-example.cpp
//   make submit SRC=example/fps-example.cpp

#include <atcoder/all>

#include <iostream>

#include "math/combinatorics/mod-sqrt.hpp"
#include "math/fps/formal-power-series-friendly-ntt.hpp"

using mint = atcoder::modint998244353;

int main() {
  FPS<mint> f = {1, 1};
  auto g = f.inv(5);  // 1 - x + x^2 - x^3 + x^4
  for (auto v : g) std::cout << v.val() << ' ';
  std::cout << '\n';

  // 定数項が 1 でない級数の平方根は mod_sqrt を渡す。
  // mod_sqrt は解がないとき -1 を返すが、sqrt が二乗して確かめるのでそのまま渡してよい。
  auto get_sqrt = [](mint x) {
    return mint(mod_sqrt<long long>(x.val(), mint::mod()));
  };
  FPS<mint> h = {9, 12, 4, 0, 0};
  for (auto v : h.sqrt(5, get_sqrt)) std::cout << v.val() << ' ';
  std::cout << '\n';
  return 0;
}
