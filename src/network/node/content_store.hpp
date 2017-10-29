#ifndef CONTENT_STORE_HPP
#define CONTENT_STORE_HPP

#include <string>

#include "./cache/policy.hpp"

namespace network {
    namespace node {
        namespace protocol {
            class data_packet;
            typedef struct data_packet_content data_packet_content;
        }

        namespace cache {
            typedef struct data_packet_meta data_packet_meta;
        }

        class content_store {
        private:
            bool m_tracking_enabled;

            network::node::cache::policy* m_policy;

        public:
            content_store(network::node::cache::policy* policy);
            ~content_store();

            void enable_tracking();

            bool has(std::string id);
            network::node::protocol::data_packet_content* get(std::string id);
            void put(protocol::data_packet packet, cache::data_packet_meta meta);
        };
    }
}

#endif