#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include <atcoder/modint>

#include <cstdint>
#include <iostream>

#include "math/fps/formal-power-series-friendly-ntt.hpp"

using mint = atcoder::modint998244353;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::int64_t k;
  std::cin >> n >> k;
  FPS<mint> a(n);
  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    a[i] = x;
  }
  FPS<mint> b = a.pow(k, n);
  for (int i = 0; i < n; i++) {
    std::cout << b[i].val() << " \n"[i + 1 == n];
  }
  return 0;
}
