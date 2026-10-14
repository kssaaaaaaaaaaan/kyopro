#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include <atcoder/modint>

#include <iostream>

#include "math/fps/formal-power-series-friendly-ntt.hpp"

using mint = atcoder::modint998244353;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  FPS<mint> f(n), g(m);
  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    f[i] = x;
  }
  for (int i = 0; i < m; i++) {
    int x;
    std::cin >> x;
    g[i] = x;
  }
  auto [q, r] = f.div_mod(g);
  q.shrink();
  r.shrink();
  std::cout << q.size() << ' ' << r.size() << '\n';
  for (int i = 0; i < (int)q.size(); i++) {
    std::cout << q[i].val() << " \n"[i + 1 == (int)q.size()];
  }
  if (q.empty()) std::cout << '\n';
  for (int i = 0; i < (int)r.size(); i++) {
    std::cout << r[i].val() << " \n"[i + 1 == (int)r.size()];
  }
  if (r.empty()) std::cout << '\n';
  return 0;
}
