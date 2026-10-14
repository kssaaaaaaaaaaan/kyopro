#pragma once
#ifdef __clang__

namespace __gnu_pbds {
struct tree_order_statistics_node_update {};
}

#else
#include_next <ext/pb_ds/tree_policy.hpp>
#endif
