#ifndef POLICY_HPP
#define POLICY_HPP

#include <string>

namespace network {
    namespace protocol {
        class data_packet;
    }

    namespace node {
        namespace cache {
            class policy {
            public:
                policy();
                virtual ~policy();

                virtual bool has(std::string id) = 0;
                virtual network::protocol::data_packet get(std::string id) = 0;
                virtual void put(network::protocol::data_packet packet) = 0;
            };
        }
    }
}

#endif