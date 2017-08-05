#include <iostream>

#include "./../../lib/easylogging++.h"
#include "network_simulator.hpp"

network::network_simulator::network_simulator(node::network_node **&nodes) {
    this->m_nodes = nodes;
}

network::network_simulator::~network_simulator() {
    // delete m_threads
    LOG(INFO) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Destroying threads";
    std::list<std::thread*>::iterator thread_i;

    for (thread_i = this->m_threads.begin(); thread_i != this->m_threads.end(); ++thread_i) {
        (*thread_i)->join();
        delete *thread_i;
    }

    // delete m_nodes
    LOG(INFO) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Destroying nodes";
    for (int i = 0; this->m_nodes[i] != nullptr; i++)
        delete this->m_nodes[i];

    delete[] this->m_nodes;
}

void network::network_simulator::start() {
    // start up threads
    LOG(INFO) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Starting simulation";
    LOG(INFO) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Starting up threads";

    for (int i = 0; this->m_nodes[i] != nullptr; i++) {
        std::thread* t = new std::thread(
            [&] (node::network_node* node) { node->run(); },
            this->m_nodes[i]
        );

        this->m_threads.push_back(t);
    }
}