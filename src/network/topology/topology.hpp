#ifndef TOPOLOGY_HPP
#define TOPOLOGY_HPP

#include <list>

namespace network {
    namespace node {
        class network_node;
    }

    namespace topology {
        typedef struct topology_config {
            int number_of_nodes = 50;
            int max_number_of_nodes_in_clusters = 5;
        } topology_config;

        class topology {
        public:
            topology() {};
            virtual ~topology() {};

            virtual network::node::network_node** generate(topology_config* config) = 0;
        };
    }
}

#endif