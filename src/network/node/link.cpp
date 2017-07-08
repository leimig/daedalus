#include <random>

#include "link.hpp"

network::node::link::link(network_node* forwarding_node) {
    this->m_forwarding_node = forwarding_node;
    this->m_delay = 100;
    this->m_variation = 20;
}

network::node::link::link(network_node* forwarding_node, int delay, int variation) {
    this->m_forwarding_node = forwarding_node;
    this->m_delay = delay;
    this->m_variation = variation;
}

/**
 * link destructor is not responsible for deleting the forwarding_node pointer.
 */
network::node::link::~link() { }

int network::node::link::delay() {
    int max = this->m_delay + this->m_variation;
    int min = this->m_delay - this->m_variation;

    return (std::rand() % (max - min + 1)) + min;
}