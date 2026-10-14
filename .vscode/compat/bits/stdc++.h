#pragma once
#ifdef __clang__
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// libc++ は __int128 の abs / numeric_limits を提供しないため補完
inline __int128 abs(__int128 x) noexcept { return x < 0 ? -x : x; }
namespace std {
template <> struct numeric_limits<__int128> {
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed      = true;
    static constexpr bool is_integer     = true;
    static constexpr __int128 max() noexcept {
        return ((__int128)1 << 126) + (((__int128)1 << 126) - 1);
    }
    static constexpr __int128 min() noexcept { return -max() - 1; }
    static constexpr __int128 lowest() noexcept { return min(); }
};
} // namespace std

#else
#include_next <bits/stdc++.h>
#endif
