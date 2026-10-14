#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include <atcoder/modint>

#include <iostream>

#include "math/fps/formal-power-series-friendly-ntt.hpp"
#include "math/combinatorics/mod-sqrt.hpp"

using mint = atcoder::modint998244353;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  FPS<mint> a(n);
  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    a[i] = x;
  }
  // mod_sqrt は解がないとき -1 を返すが、sqrt が二乗して確かめるのでそのまま渡してよい。
  auto get_sqrt = [](mint x) {
    return mint(mod_sqrt<long long>(x.val(), mint::mod()));
  };
  FPS<mint> b = a.sqrt(n, get_sqrt);
  if (b.empty()) {
    std::cout << -1 << '\n';
    return 0;
  }
  for (int i = 0; i < n; i++) {
    std::cout << b[i].val() << " \n"[i + 1 == n];
  }
  return 0;
}
