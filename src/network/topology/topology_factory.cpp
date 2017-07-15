#include "./topology_factory.hpp"
#include "./topology.hpp"
#include "./graph_topology.hpp"

const std::string network::topology::topology_factory::GRAPH_TYPE = "GRAPH";

network::topology::topology_factory::topology_factory() {

}

network::topology::topology_factory::~topology_factory() {

}

network::topology::topology* network::topology::topology_factory::get(std::string type) {
    if (type == network::topology::topology_factory::GRAPH_TYPE) {
        return new graph_topology;
    }

    return NULL;
}