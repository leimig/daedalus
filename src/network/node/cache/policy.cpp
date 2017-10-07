#include "./policy.hpp"
#include "./no_cache.hpp"

network::node::cache::policy* network::node::cache::policy::make(std::string id) {
    if (id == network::node::cache::no_cache::id)
        return new network::node::cache::no_cache;

    return nullptr;
}