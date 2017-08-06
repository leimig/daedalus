#ifndef TOPOLOGY_HPP
#define TOPOLOGY_HPP

#include <list>

namespace network {
    struct network_config;
    typedef network_config network_config;

    namespace node {
        class network_node;
    }

    namespace topology {
        class topology {
        public:
            topology() {};
            virtual ~topology() {};

            virtual network::node::network_node** generate(network_config* config) = 0;
        };
    }
}

#endif