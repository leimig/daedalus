#ifndef LFU_HPP
#define LFU_HPP

#include <string>
#include <list>

#include "./policy.hpp"

namespace network {
    namespace node {
        namespace cache {
            typedef struct lfu_entry {
                std::string packet_id;
                int frequency_count = 1;
            } lfu_entry;

            class lfu : public policy {
            private:
                std::list<lfu_entry> m_data;

            public:
                static const std::string id;

                lfu(int cache_size);
                ~lfu();

                bool has(std::string packet_id);
                network::node::protocol::data_packet_content* get(std::string packet_id);
                void put(network::node::protocol::data_packet packet, data_packet_meta meta);
            };
        }
    }
}

#endif