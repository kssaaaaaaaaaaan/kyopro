#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <atcoder/modint>

#include <iostream>
#include <vector>

#include "math/fps/formal-power-series-friendly-ntt.hpp"

using mint = atcoder::modint998244353;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  FPS<mint> a(n), b(m);
  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    a[i] = x;
  }
  for (int i = 0; i < m; i++) {
    int x;
    std::cin >> x;
    b[i] = x;
  }
  FPS<mint> c = a * b;
  for (int i = 0; i < (int)c.size(); i++) {
    std::cout << c[i].val() << " \n"[i + 1 == (int)c.size()];
  }
  return 0;
}
