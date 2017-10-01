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

void network::network_simulator::run() {
    srand((int) time(0));

    this->warmup();
    this->simulate();
}

void network::network_simulator::warmup() {
    VLOG(1) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Warming up";

    for (int i = 0; i < this->m_config.warmup_size; i++) {
        this->send_interest_packet();
    }
}

void network::network_simulator::simulate() {
    VLOG(1) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Starting simulation";

    for (int i = 0; i < this->m_config.round_size; i++) {
        this->send_interest_packet();
    }
}

void network::network_simulator::send_interest_packet() {
    int sender_id = (rand() % this->m_config.network_three_size) + 1;
    std::string packet_id = std::to_string((rand() % this->m_config.number_of_packets) + 1);

    node::protocol::interest_packet packet(sender_id, packet_id);
    this->m_node->handle(packet);
}

void network::network_simulator::handle(node::protocol::packet packet) {
    if (network::node::protocol::interest_packet* p = dynamic_cast<network::node::protocol::interest_packet*>(&packet)) {
        this->handle_lookup(*p);
    } else if (network::node::protocol::data_packet* p = dynamic_cast<network::node::protocol::data_packet*>(&packet)) {
        this->handle_answer(*p);
    }
}

void network::network_simulator::handle_lookup(node::protocol::interest_packet packet) {
    // Queue the request and answer after some time
}

void network::network_simulator::handle_answer(node::protocol::data_packet packet) {
    // Do nothing
}