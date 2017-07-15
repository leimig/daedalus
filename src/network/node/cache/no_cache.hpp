#ifndef NO_CACHE_HPP
#define NO_CACHE_HPP

#include <string>

#include "./policy.hpp"

namespace network {
    namespace node {
        namespace cache {
            class node_cache : public policy {

            public:
                node_cache() {}
                ~node_cache() {}

                bool has(std::string id) { return false; }
                network::node::protocol::data_packet get(std::string id) { return NULL };
                void put(network::node::protocol::data_packet packet) {};
            };
        }
    }
}

#endif