#include <iostream>
#include <string>
#include <ctime>

#include "./../../lib/easylogging++.h"
#include "./node/cache/no_cache.hpp"
#include "network_simulator.hpp"

network::network_simulator::network_simulator(network::network_config config) {
    this->m_config = config;
    this->m_node = new network::node::network_node(0, this, new network::node::cache::no_cache);

    this->m_round_step = 0;
    this->m_warmup_step = 0;
}

network::network_simulator::~network_simulator() {
    delete this->m_node;
}

void network::network_simulator::run() {
    srand((int) time(0));

    VLOG(1) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Warming up";

    while (true) {
        network::node::protocol::interest_packet *p = this->next_lookup_to_answer();

        if (this->is_warmup_active()) {
            this->send_interest_packet();
            this->m_warmup_step++;
        }

        if (p) {
            // answer lookup packet
        }

        if (!this->is_warmup_active() && p == NULL) {
            break;
        }
    }

    VLOG(1) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Starting simulation";

    while (true) {
        network::node::protocol::interest_packet *p = this->next_lookup_to_answer();

        if (this->is_round_active()) {
            this->send_interest_packet();
            this->m_round_step++;
        }

        if (p) {
            // answer lookup packet
        }

        if (!this->is_warmup_active() && p == NULL) {
            break;
        }
    }
}

bool network::network_simulator::is_warmup_active() {
    return this->m_warmup_step < this->m_config.warmup_size;
}

bool network::network_simulator::is_round_active() {
    return this->m_round_step < this->m_config.round_size;
}

network::node::protocol::interest_packet* network::network_simulator::next_lookup_to_answer() {
    return NULL;
}

void network::network_simulator::send_interest_packet() {
    int sender_id = (rand() % this->m_config.network_three_size) + 1;
    std::string packet_id = std::to_string((rand() % this->m_config.number_of_packets) + 1);

    network::node::protocol::interest_packet packet(sender_id, packet_id);
    this->m_node->handle(packet);
}

void network::network_simulator::handle(node::protocol::packet packet) {
    if (network::node::protocol::interest_packet* p = dynamic_cast<network::node::protocol::interest_packet*>(&packet)) {
        this->handle_lookup(*p);
        delete p;

    } else if (network::node::protocol::data_packet* p = dynamic_cast<network::node::protocol::data_packet*>(&packet)) {
        this->handle_answer(*p);
        delete p;
    }
}

void network::network_simulator::handle_lookup(node::protocol::interest_packet packet) {

}

void network::network_simulator::handle_answer(node::protocol::data_packet packet) {
    // Do nothing
}