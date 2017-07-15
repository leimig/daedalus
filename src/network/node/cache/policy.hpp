#ifndef POLICY_HPP
#define POLICY_HPP

#include <string>

namespace network {
    namespace node {
        namespace protocol {
            class data_packet;
        }

        namespace cache {
            class policy {
            public:
                policy() {};
                virtual ~policy() {};

                virtual bool has(std::string id) = 0;
                virtual network::node::protocol::data_packet* get(std::string id) = 0;
                virtual void put(network::node::protocol::data_packet packet) = 0;
            };
        }
    }
}

#endif