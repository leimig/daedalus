#include <iostream>

#include "./../../lib/easylogging++.h"
#include "./node/cache/no_cache.hpp"
#include "./node/cache/no_cache.hpp"
#include "network_simulator.hpp"

network::network_simulator::network_simulator(network::network_config config) {
    this->m_config = config;
    this->m_node = new network::node::network_node(1, this, new network::node::cache::no_cache);
}

network::network_simulator::~network_simulator() {

}

void network::network_simulator::start() {
    // start up threads
    LOG(INFO) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Starting simulation";

    // for (int i = 0; this->m_nodes[i] != nullptr; i++) {
    //     std::thread* t = new std::thread(thread_loop, this);
    //     this->m_threads.push_back(t);
    // }
}

void network::network_simulator::lookup(node::protocol::interest_packet packet) {

}

void network::network_simulator::respond(int id, node::protocol::data_packet packet) {

}