#include "./policy.hpp"
#include "./no_cache.hpp"
#include "./fifo.hpp"

network::node::cache::policy* network::node::cache::policy::make(std::string id) {
    if (id == network::node::cache::no_cache::id)
        return new network::node::cache::no_cache;

    if (id == network::node::cache::fifo::id)
        return new network::node::cache::fifo;

    return nullptr;
}