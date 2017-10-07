#ifndef POLICY_HPP
#define POLICY_HPP

#include <string>

namespace network {
    namespace node {
        namespace protocol {
            class data_packet;
            typedef struct data_packet_content data_packet_content;
        }

        namespace cache {
            class policy {
            public:
                policy() {};
                virtual ~policy() {};

                static network::node::cache::policy* make(std::string id);

                virtual bool has(std::string packet_id) = 0;
                virtual network::node::protocol::data_packet_content* get(std::string packet_id) = 0;
                virtual void put(network::node::protocol::data_packet packet) = 0;
            };
        }
    }
}

#endif