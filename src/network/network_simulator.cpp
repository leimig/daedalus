#include <iostream>
#include <string>
#include <ctime>

#include "./../../lib/easylogging++.h"
#include "./node/cache/no_cache.hpp"
#include "./node/cache/no_cache.hpp"
#include "network_simulator.hpp"

network::network_simulator::network_simulator(network::network_config config) {
    this->m_config = config;
    this->m_node = new network::node::network_node(0, this, new network::node::cache::no_cache);
}

network::network_simulator::~network_simulator() {
    delete this->m_node;
}

void network::network_simulator::start() {
    srand((int) time(0));

    VLOG(0) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Starting simulation";

    this->warmup();

    // for (int i = 0; this->m_nodes[i] != nullptr; i++) {
    //     std::thread* t = new std::thread(thread_loop, this);
    //     this->m_threads.push_back(t);
    // }
}

void network::network_simulator::warmup() {
    for (int i = 0; i < this->m_config.warmup_size; i++) {
        int sender_id = (rand() % this->m_config.network_three_size) + 1;
        std::string packet_id = std::to_string((rand() % this->m_config.number_of_packets) + 1);

        node::protocol::interest_packet packet(sender_id, packet_id);
        this->m_node->lookup(packet);
    }
}

void network::network_simulator::lookup(node::protocol::interest_packet packet) {

}

void network::network_simulator::respond(int id, node::protocol::data_packet packet) {

}