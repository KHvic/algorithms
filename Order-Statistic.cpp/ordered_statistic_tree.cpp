#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename K, typename V, typename Comp = std::less<K>>
using order_statistic_map = __gnu_pbds::tree<
	K, V, Comp,
	__gnu_pbds::rb_tree_tag,
	__gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = std::less<K>>
using OS = order_statistic_map<K, __gnu_pbds::null_type, Comp>;


int main(){
    vector<int> test = {1,5,8,10,15};
    OS<int> os(test.begin(), test.end());

    // return x smallest item
    auto it = os.find_by_order(1);
    cout << *it << "\n"; // 5
    // find rank of item
    cout << os.order_of_key(10) << "\n"; // 3
}
