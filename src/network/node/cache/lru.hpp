#ifndef LRU_HPP
#define LRU_HPP

#include <string>
#include <list>

#include "./policy.hpp"

namespace network {
    namespace node {
        namespace cache {
            class lru : public policy {
            private:
                std::list<std::string> m_data;

            public:
                static const std::string id;

                lru(int cache_size);
                ~lru();

                bool has(std::string packet_id);
                network::node::protocol::data_packet_content* get(std::string packet_id);
                void put(network::node::protocol::data_packet packet, data_packet_meta meta);
            };
        }
    }
}

#endif