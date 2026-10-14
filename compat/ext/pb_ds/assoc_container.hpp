#pragma once
#ifdef __clang__
#include <set>
#include <unordered_map>
#include <iterator>

namespace __gnu_pbds {

struct null_type {};
struct rb_tree_tag {};

// order statistics tree
template <typename Key,
          typename Mapped,
          typename Cmp = std::less<Key>,
          typename Tag = rb_tree_tag,
          typename Node_Update = null_type>
class tree : public std::set<Key, Cmp> {
    using base = std::set<Key, Cmp>;
public:
    size_t order_of_key(const Key& k) const {
        return static_cast<size_t>(
            std::distance(base::begin(), base::lower_bound(k)));
    }
    typename base::const_iterator find_by_order(size_t n) const {
        auto it = base::begin();
        std::advance(it, static_cast<typename base::difference_type>(n));
        return it;
    }
};

// chaining hash table (unordered_map 互換シム)
template <typename Key, typename Mapped,
          typename Hash = std::hash<Key>,
          typename... Rest>
class cc_hash_table : public std::unordered_map<Key, Mapped, Hash> {
    using base = std::unordered_map<Key, Mapped, Hash>;
public:
    using base::base;
};

// open-addressing hash table (gp_hash_table は erase 非対応だが shim では継承)
template <typename Key, typename Mapped,
          typename Hash = std::hash<Key>,
          typename... Rest>
class gp_hash_table : public std::unordered_map<Key, Mapped, Hash> {
    using base = std::unordered_map<Key, Mapped, Hash>;
public:
    using base::base;
};

} // namespace __gnu_pbds

#else
#include_next <ext/pb_ds/assoc_container.hpp>
#endif
