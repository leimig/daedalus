#include "./policy.hpp"
#include "./no_cache.hpp"
#include "./climb.hpp"
#include "./fifo.hpp"
#include "./lifo.hpp"
#include "./lru.hpp"

network::node::cache::policy* network::node::cache::policy::make(std::string id, int cache_size) {
    if (id == network::node::cache::no_cache::id)
        return new network::node::cache::no_cache(cache_size);

    if (id == network::node::cache::fifo::id)
        return new network::node::cache::fifo(cache_size);

    if (id == network::node::cache::lifo::id)
        return new network::node::cache::lifo(cache_size);

    if (id == network::node::cache::lru::id)
        return new network::node::cache::lru(cache_size);

    if (id == network::node::cache::climb::id)
        return new network::node::cache::climb(cache_size);

    return nullptr;
}