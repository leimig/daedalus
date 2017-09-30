#include <thread>

#include "./../../../lib/easylogging++.h"
#include "./network_node.hpp"
#include "./protocol/data_packet.hpp"
#include "./protocol/interest_packet.hpp"
#include "./content_store.hpp"

network::node::network_node::network_node(network::node::network_interface* interface, network::node::cache::policy* policy) {
    this->m_store = new content_store(policy);
    this->m_interface = interface;
}

network::node::network_node::~network_node() {
    delete this->m_store;
    // this->m_interface is not responsibility of the network_node
}

void network::node::network_node::lookup(network::node::protocol::interest_packet packet) {
    LOG(INFO) << "[DAEDALUS][NETWORK_NODE] " << "Receiving Interest Packet for " << packet.id();
    if (this->m_store->has(packet.id())) {
        network::node::protocol::data_packet* data_packet = this->m_store->get(packet.id());
        // TODO: Send through this->m_interface
        // packet.sender()->receive(*data_packet);

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

            // TODO: Send through this->m_interface
            // std::list<link*>::iterator link_i;

            // for (link_i = this->m_forwarding_nodes.begin(); link_i != this->m_forwarding_nodes.end(); ++link_i) {
            //     network::node::protocol::interest_packet i_p(this, packet.id());
            //     if ((*link_i)->forwarding_node()->id() != packet.sender()->id()) {
            //         (*link_i)->forwarding_node()->lookup(i_p);
            //     }
            // }

        } else {
            pit_entry entry;
            entry.node = packet.sender();
            entry.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            );

            this->m_pending_interest_table[packet.id()].push_back(entry);
        }
    }
}

void network::node::network_node::receive(network::node::protocol::data_packet packet) {
    LOG(INFO) << "[DAEDALUS][NETWORK_NODE] " << "Receiving Data Packet for " << packet.id();

    if (this->m_pending_interest_table.count(packet.id()) == 1) {
        std::list<pit_entry> pending = this->m_pending_interest_table[packet.id()];

        std::list<pit_entry>::iterator entry_i;

        for (entry_i = pending.begin(); entry_i != pending.end(); ++entry_i) {
            // TODO: Send through this->m_interface
            // entry_i->node->receive(packet);
        }
    }

    this->m_store->put(packet);
}