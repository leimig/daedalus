#include <iostream>

#include "./../../lib/easylogging++.h"
#include "network_simulator.hpp"

void thread_loop(network::network_simulator *simulator);

network::network_simulator::network_simulator(network::network_config config, node::network_node **&nodes) {
    this->m_nodes = nodes;
    this->m_config = config;
    this->m_last_thread_index = 0;
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
        std::thread* t = new std::thread(thread_loop, this);
        this->m_threads.push_back(t);
    }
}

network::node::network_node* network::network_simulator::next_node() {
    this->m_next_thread_mutex.lock();

    int curr_node_index = this->m_last_thread_index;

    network::node::network_node *node = nullptr;
    network::node::network_node *tmp_node = nullptr;

    while (node == nullptr) {
        tmp_node = this->m_nodes[curr_node_index];

        if (tmp_node->has_pending_requests()) {
            this->m_last_thread_index = curr_node_index;
            node = tmp_node;

        } else {
            curr_node_index = (curr_node_index + 1) % this->m_config.number_of_nodes;

            if (curr_node_index == this->m_last_thread_index) {
                break; // didn't find any node with work to be done
            }
        }
    }

    this->m_next_thread_mutex.unlock();
    return node;
}

void thread_loop(network::network_simulator *simulator) {
    network::node::network_node *node = nullptr;

    while (node != nullptr) {
        node->run();
        node = simulator->next_node();
    }
}