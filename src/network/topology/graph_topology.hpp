#ifndef TOPOLOGY_GRAPH_HPP
#define TOPOLOGY_GRAPH_HPP

#include "./topology.hpp"

namespace network {
    namespace node {
        class network_node;
    }

    namespace topology {
        class graph_topology : public topology {
        public:
            graph_topology();
            ~graph_topology();

            std::list<network::node::network_node*> generate(network::topology::topology_config* config);
        };
    }
}

#endif