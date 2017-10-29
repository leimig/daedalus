#include <iostream>
#include <string>
#include <ctime>
#include <thread>

#include "./../../lib/easylogging++.h"
#include "./../../lib/zipf.c"
#include "./node/cache/policy.hpp"
#include "network_simulator.hpp"

network::network_simulator::network_simulator(network::network_config config) {
    this->m_config = config;
    this->m_node = new network::node::network_node(
        this->m_config.network_three_size + 1,
        network::node::cache::policy::make(config.policy_name, config.cache_size),
        this
    );

    this->m_round_step = 0;
    this->m_warmup_step = 0;
}

network::network_simulator::~network_simulator() {
    delete this->m_node;
}

int network::network_simulator::id() {
    return 0;
}

void network::network_simulator::run() {
    rand_val((int) time(0));

    VLOG(1) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Warming up";
    this->run_round(&this->m_warmup_step, &this->m_config.warmup_size);

    this->m_node->enable_tracking();

    VLOG(1) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Running simulation";
    this->run_round(&this->m_round_step, &this->m_config.round_size);

    VLOG(1) << "[DAEDALUS][NETWORK_SIMULATOR] " << "Wrapping up simulation";
}

void network::network_simulator::run_round(int* step, int* size) {
    while (true) {
        if (*step < *size) {
            this->send_interest_packet();
            (*step)++;
        }

        std::shared_ptr<network::node::protocol::data_packet> p = nullptr;

        do {
            p = this->next_lookup_to_answer();

            if (p) {
                this->m_node->handle_answer(*p);
            }
        } while(p);

        if (*step >= *size && p == nullptr) {
            break;
        }

        std::this_thread::yield();
    }
}

std::shared_ptr<network::node::protocol::data_packet> network::network_simulator::next_lookup_to_answer() {
    if (this->m_received_lookups.empty()) {
        return nullptr;
    }

    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::shared_ptr<network::node::protocol::data_packet> packet_ptr;

    std::list<received_lookup>::iterator it;

    for (it = this->m_received_lookups.begin(); it != this->m_received_lookups.end(); it++) {
        received_lookup entry = *it;

        if (entry.response_timestamp <= now) {
            packet_ptr = std::make_shared<network::node::protocol::data_packet>(
                network::node::protocol::data_packet(0, this->m_node->id(), entry.packet_id)
            );

            break;
        }
    }

    if (packet_ptr) {
        this->m_received_lookups.erase(it);
    }

    return packet_ptr;
}

void network::network_simulator::send_interest_packet() {
    int sender_id = (rand() % this->m_config.network_three_size) + 1;
    std::string packet_id = std::to_string(zipf(this->m_config.zipf_distribution_alpha, this->m_config.number_of_packets) + 1);

    network::node::protocol::interest_packet packet(sender_id, packet_id);
    this->m_node->handle_lookup(packet);
}

void network::network_simulator::handle_lookup(network::node::protocol::interest_packet packet) {
    VLOG(9) << "[DAEDALUS][NETWORK_NODE] "
        << "Receiving Interest Packet for " << packet.packet_id();

    received_lookup entry;
    entry.packet_id = packet.packet_id();

    auto delay = std::chrono::milliseconds((rand() % 320) + 1);
    auto now = std::chrono::system_clock::now().time_since_epoch();

    entry.response_timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now + delay);

    this->m_received_lookups.push_back(entry);
}

void network::network_simulator::handle_answer(network::node::protocol::data_packet packet) {
    // Do nothing
}