#include <thread>

#include "./../../../lib/easylogging++.h"
#include "./link.hpp"
#include "./network_node.hpp"
#include "./protocol/data_packet.hpp"
#include "./protocol/interest_packet.hpp"
#include "./content_store.hpp"
#include "./cache/no_cache.hpp"

network::node::network_node::network_node(int id, network::node::cache::policy* policy) {
    this->m_id = id;
    this->m_store = new content_store(policy);
}

network::node::network_node::~network_node() {
    // delete m_forwarding_nodes
    for (auto link_i = this->m_forwarding_nodes.begin(); link_i != this->m_forwarding_nodes.end(); ++link_i) {
        delete *link_i;
    }

    delete this->m_store;
}

int network::node::network_node::id() {
    return this->m_id;
}

void network::node::network_node::run() {
    // Need to find another way to finish node's thread
    while (!this->m_lookup_requests.empty() && !this->m_response_requests.empty()) {
        LOG(INFO) << "[NETWORK_NODE] " << "Verifying for incoming packets";

        this->handle_lookup_request();

        std::this_thread::yield();

        this->handle_response_request();

        std::this_thread::yield();
    }

    LOG(INFO) << "[NETWORK_NODE] " << "Finishing execution";
}

void network::node::network_node::handle_lookup_request() {
    if (!this->m_lookup_requests.empty()) {
        network::node::protocol::interest_packet packet = this->m_lookup_requests.front();

        if (this->m_store->has(packet.id())) {
            network::node::protocol::data_packet* data_packet = this->m_store->get(packet.id());
            packet.sender()->receive(*data_packet);

        } else {

            if (this->m_pending_interest_table.count(packet.id()) == 0) {
                pit_entry entry;
                entry.node = packet.sender();
                entry.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                );

                std::list<pit_entry> l;
                l.push_back(entry);

                this->m_pending_interest_table[packet.id()] = l;

                std::list<link*>::iterator link_i;

                for (link_i = this->m_forwarding_nodes.begin(); link_i != this->m_forwarding_nodes.end(); ++link_i) {
                    network::node::protocol::interest_packet i_p(this, packet.id());
                    if ((*link_i)->forwarding_node()->id() != packet.sender()->id()) {
                        (*link_i)->forwarding_node()->lookup(i_p);
                    }
                }

            } else {
                pit_entry entry;
                entry.node = packet.sender();
                entry.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                );

                this->m_pending_interest_table[packet.id()].push_back(entry);
            }
        }

        this->m_lookup_requests.pop_front();
    }
}

void network::node::network_node::handle_response_request() {
    if (!this->m_response_requests.empty()) {
        network::node::protocol::data_packet packet = this->m_response_requests.front();

        if (this->m_pending_interest_table.count(packet.id()) == 1) {
            std::list<pit_entry> pending = this->m_pending_interest_table[packet.id()];

            std::list<pit_entry>::iterator entry_i;

            for (entry_i = pending.begin(); entry_i != pending.end(); ++entry_i) {
                entry_i->node->receive(packet);
            }
        }

        this->m_store->put(packet);
        this->m_response_requests.pop_front();
    }
}

void network::node::network_node::register_forwarding_node(network_node* forwarding_node) {
    this->m_forwarding_nodes.push_back(new link(forwarding_node));
}

void network::node::network_node::lookup(network::node::protocol::interest_packet packet) {
    LOG(INFO) << "[NETWORK_NODE] " << "Receiving Interest Packet for " << packet.id();
    this->m_lookup_requests.push_back(packet);
}

void network::node::network_node::receive(network::node::protocol::data_packet packet) {
    LOG(INFO) << "[NETWORK_NODE] " << "Receiving Data Packet for " << packet.id();
    this->m_response_requests.push_back(packet);
}