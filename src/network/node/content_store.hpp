#ifndef CONTENT_STORE_HPP
#define CONTENT_STORE_HPP

#include <string>

#include "./cache/policy.hpp"

namespace network {
    namespace node {
        namespace protocol {
            class data_packet;
        }

        class content_store {
        private:
            network::node::cache::policy* m_policy;

        public:
            content_store(network::node::cache::policy* policy);
            ~content_store();

            bool has(std::string id);
            protocol::data_packet* get(std::string id);
            void put(protocol::data_packet packet);
        };
    }
}

#endif