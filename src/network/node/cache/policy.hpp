#ifndef POLICY_HPP
#define POLICY_HPP

#include <chrono>
#include <string>

namespace network {
    namespace node {
        namespace protocol {
            class data_packet;
            typedef struct data_packet_content data_packet_content;
        }

        namespace cache {
            typedef struct data_packet_meta {
                std::chrono::milliseconds delay;
            } data_packet_meta;

            class policy {
                int m_cache_size;

            public:
                policy(int cache_size) {
                    this->m_cache_size = cache_size;
                };

                virtual ~policy() {};

                static network::node::cache::policy* make(std::string id, int cache_size);

                int cache_size() { return this->m_cache_size; };

                virtual bool has(std::string packet_id) = 0;
                virtual network::node::protocol::data_packet_content* get(std::string packet_id) = 0;
                virtual void put(network::node::protocol::data_packet packet, data_packet_meta meta) = 0;
            };
        }
    }
}

#endif