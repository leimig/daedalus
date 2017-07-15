#include <random>

#include "link.hpp"

network::node::link::link(network_node* forwarding_node) {
    this->m_forwarding_node = forwarding_node;
}

/**
 * link destructor is not responsible for deleting the forwarding_node pointer.
 */
network::node::link::~link() { }