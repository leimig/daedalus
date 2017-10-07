#ifndef NO_CACHE_HPP
#define NO_CACHE_HPP

#include <string>

#include "./policy.hpp"

namespace network {
    namespace node {
        namespace cache {
            class no_cache : public policy {

            public:
                static const std::string id;

                no_cache();
                ~no_cache();

                bool has(std::string packet_id);
                network::node::protocol::data_packet* get(std::string packet_id);
                void put(network::node::protocol::data_packet packet);
            };
        }
    }
}

#endif