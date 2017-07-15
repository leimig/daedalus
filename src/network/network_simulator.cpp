#include <iostream>

#include "./../../lib/easylogging++.h"
#include "network_simulator.hpp"

network::network_simulator::network_simulator(std::list<node::network_node*> nodes) {
    this->m_nodes = nodes;
}

network::network_simulator::~network_simulator() {
    // delete m_threads
    LOG(INFO) << "[NETWORK_SIMULATOR] " << "Destroying threads";
    std::list<std::thread*>::iterator thread_i;

    for (thread_i = this->m_threads.begin(); thread_i != this->m_threads.end(); ++thread_i) {
        (*thread_i)->join();
        delete *thread_i;
    }

    // delete m_nodes
    LOG(INFO) << "[NETWORK_SIMULATOR] " << "Destroying nodes";
    std::list<node::network_node*>::iterator node_i;

    for (node_i = this->m_nodes.begin(); node_i != this->m_nodes.end(); ++node_i)
        delete *node_i;
}

void network::network_simulator::start() {
    // start up threads
    LOG(INFO) << "[NETWORK_SIMULATOR] " << "Starting simulation";
    LOG(INFO) << "[NETWORK_SIMULATOR] " << "Starting up threads";
    std::list<node::network_node*>::iterator node_i;

    for (node_i = this->m_nodes.begin(); node_i != this->m_nodes.end(); ++node_i) {
        std::thread* t = new std::thread([&] (node::network_node* node) { node->run(); }, *node_i);
        this->m_threads.push_back(t);
    }
}