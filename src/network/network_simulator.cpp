#include <iostream>

#include "network_simulator.hpp"

network::network_simulator::network_simulator(int n_nodes) {
    for (int i = 0; i < n_nodes; i++) {
        this->m_nodes.push_back(new node::network_node);
    }
}

network::network_simulator::~network_simulator() {
    // delete m_threads
    std::list<std::thread*>::iterator thread_i;

    for (thread_i = this->m_threads.begin(); thread_i != this->m_threads.end(); ++thread_i) {
        (*thread_i)->join();
        delete *thread_i;
    }

    // delete m_nodes
    std::list<node::network_node*>::iterator node_i;

    for (node_i = this->m_nodes.begin(); node_i != this->m_nodes.end(); ++node_i)
        delete *node_i;
}

void network::network_simulator::start() {
    // delete m_nodes
    std::list<node::network_node*>::iterator node_i;

    for (node_i = this->m_nodes.begin(); node_i != this->m_nodes.end(); ++node_i) {
        std::thread* t = new std::thread([&] (node::network_node* node) { node->run(); }, *node_i);
        this->m_threads.push_back(t);
    }
}