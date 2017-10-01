#include <thread>

#include "./../../../lib/easylogging++.h"
#include "./content_store.hpp"
#include "./network_node.hpp"
#include "./network_interface.hpp"
#include "./protocol/data_packet.hpp"
#include "./protocol/interest_packet.hpp"

network::node::network_node::network_node(int id, network::node::network_interface* interface, network::node::cache::policy* policy) {
    this->m_id = id;
    this->m_store = new content_store(policy);
    this->m_interface = interface;
}

network::node::network_node::~network_node() {
    delete this->m_store;
    // this->m_interface is not responsibility of the network_node
}

void network::node::network_node::handle(network::node::protocol::packet packet) {
    if (network::node::protocol::interest_packet* p = dynamic_cast<network::node::protocol::interest_packet*>(&packet)) {
        this->handle_lookup(*p);
    } else if (network::node::protocol::data_packet* p = dynamic_cast<network::node::protocol::data_packet*>(&packet)) {
        this->handle_answer(*p);
    }
}

void network::node::network_node::handle_lookup(network::node::protocol::interest_packet packet) {
    VLOG(9) << "[DAEDALUS][NETWORK_NODE] "
        << "Receiving Interest Packet for " << packet.packet_id()
        << " from node " << packet.originator_id();

    if (this->m_store->has(packet.packet_id())) {
        // calling `get` from the `content_store` allows the cache to be updated
        this->m_store->get(packet.packet_id());

        network::node::protocol::data_packet data_packet(this->m_id, packet.originator_id(), packet.packet_id());
        this->m_interface->handle(data_packet);

    } else {
        if (this->m_pending_interest_table.count(packet.packet_id()) == 0) {
            pit_entry entry;
            entry.id = packet.originator_id();
            entry.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            );

            std::list<pit_entry> l;
            l.push_back(entry);

            this->m_pending_interest_table[packet.packet_id()] = l;

            this->m_interface->handle(
                network::node::protocol::interest_packet(this->m_id, packet.packet_id())
            );

        } else {
            pit_entry entry;
            entry.id = packet.originator_id();
            entry.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            );

            this->m_pending_interest_table[packet.packet_id()].push_back(entry);
        }
    }
}

void network::node::network_node::handle_answer(network::node::protocol::data_packet packet) {
    VLOG(9) << "[DAEDALUS][NETWORK_NODE] " << "Receiving Data Packet for " << packet.packet_id();

    if (this->m_pending_interest_table.count(packet.packet_id()) == 1) {
        std::list<pit_entry> pending = this->m_pending_interest_table[packet.packet_id()];

        std::list<pit_entry>::iterator entry_i;

        for (entry_i = pending.begin(); entry_i != pending.end(); ++entry_i) {
            node::protocol::data_packet tmp_packet(this->m_id, entry_i->id, packet.packet_id());
            this->m_interface->handle(tmp_packet);
        }
    }

    this->m_store->put(packet);
}