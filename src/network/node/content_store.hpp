#ifndef CONTENT_STORE_HPP
#define CONTENT_STORE_HPP

#include <string>

#include "./cache/policy.hpp"

namespace network {
    namespace protocol {
        class data_packet;
    }

    namespace node {
        class content_store {
        private:
            network::node::cache::policy* policy;

        public:
            content_store(network::node::cache::policy* policy);
            ~content_store();

            bool has(std::string id);
            network::protocol::data_packet get(std::string id);
            void put(network::protocol::data_packet packet);
        };
    }
}

#endif