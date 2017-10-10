#include "./../../../lib/easylogging++.h"
#include "./content_store.hpp"
#include "./network_node.hpp"
#include "./network_interface.hpp"
#include "./protocol/data_packet.hpp"
#include "./protocol/interest_packet.hpp"

network::node::network_node::network_node(int id, network::node::cache::policy* policy, network::node::network_interface* interface) {
    this->m_id = id;
    this->m_store = new content_store(policy);
    this->m_interface = interface;
}

network::node::network_node::~network_node() {
    delete this->m_store;
    // this->m_interface is not responsibility of the network_node
}

void network::node::network_node::enable_tracking() {
    return this->m_store->enable_tracking();
}

void network::node::network_node::handle_lookup(network::node::protocol::interest_packet packet) {
    VLOG(9) << "[DAEDALUS][NETWORK_NODE] "
        << "Receiving Interest Packet for " << packet.packet_id()
        << " from node " << packet.originator_id();

    if (this->m_store->has(packet.packet_id())) {
        VLOG(9) << "[DAEDALUS][NETWORK_NODE] " << "Packet in cache, answering interest packet";

        // calling `get` from the `content_store` allows the cache to be updated
        network::node::protocol::data_packet_content* content = this->m_store->get(packet.packet_id());
        delete content;

        network::node::protocol::data_packet data_packet(this->m_id, packet.originator_id(), packet.packet_id());
        this->m_interface->handle_answer(data_packet);

    } else {
        VLOG(9) << "[DAEDALUS][NETWORK_NODE] " << "Packet not on cache";
        VLOG(9) << "[DAEDALUS][NETWORK_NODE] " << "Creating entry in PIT table";

        if (this->m_pending_interest_table.count(packet.packet_id()) == 0) {

            pit_entry entry;
            entry.id = packet.originator_id();
            entry.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            );

            std::list<pit_entry> l;
            l.push_back(entry);

            this->m_pending_interest_table[packet.packet_id()] = l;

        } else {
            pit_entry entry;
            entry.id = packet.originator_id();
            entry.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            );

            this->m_pending_interest_table[packet.packet_id()].push_back(entry);
        }

        VLOG(9) << "[DAEDALUS][NETWORK_NODE] " << "Looking up packet in network";
        this->m_interface->handle_lookup(
            network::node::protocol::interest_packet(this->m_id, packet.packet_id())
        );
    }
}

void network::node::network_node::handle_answer(network::node::protocol::data_packet packet) {
    VLOG(9) << "[DAEDALUS][NETWORK_NODE] " << "Receiving Data Packet for " << packet.packet_id();

    if (this->m_pending_interest_table.count(packet.packet_id()) == 1) {
        std::list<pit_entry> pending = this->m_pending_interest_table[packet.packet_id()];

        std::list<pit_entry>::iterator entry_i;

        for (entry_i = pending.begin(); entry_i != pending.end(); ++entry_i) {
            node::protocol::data_packet tmp_packet(this->m_id, entry_i->id, packet.packet_id());
            this->m_interface->handle_answer(tmp_packet);
        }
    }

    this->m_store->put(packet);
}