#include <thread>

#include "./../../../lib/easylogging++.h"
#include "./network_node.hpp"

network::node::network_node::network_node() {

}

network::node::network_node::~network_node() {
    // // delete m_lookup_requests
    // std::list<network::protocol::interest_packet*>::iterator lookup_request_i;

    // for (lookup_request_i = this->m_lookup_requests.begin(); lookup_request_i != this->m_lookup_requests.end(); ++lookup_request_i)
    //     delete *lookup_request_i;

    // // delete m_response_requests
    // std::list<network::protocol::data_packet*>::iterator response_request_i;

    // for (response_request_i = this->m_response_requests.begin(); response_request_i != this->m_response_requests.end(); ++response_request_i)
    //     delete *response_request_i;

    // delete m_forwarding_nodes
    std::list<link*>::iterator link_i;

    for (link_i = this->m_forwarding_nodes.begin(); link_i != this->m_forwarding_nodes.end(); ++link_i)
        delete *link_i;
}

void network::node::network_node::run() {
    // Need to find another way to finish node's thread
    while (!this->m_lookup_requests.empty() && !this->m_response_requests.empty()) {
        LOG(INFO) << "[NETWORK_NODE] " << "Verifying for incoming packets";

        LOG(DEBUG) << "[NETWORK_NODE] " << "Verifying incoming Interest Packets";
        if (!this->m_lookup_requests.empty()) {
            network::protocol::interest_packet packet = this->m_lookup_requests.front();

            if (false) { // check content store
                LOG(DEBUG) << "[NETWORK_NODE] " << "Data Packet found in Content Store, answering Interest Packet";
                // answer with the packet, if cached
            } else {
                LOG(DEBUG) << "[NETWORK_NODE] " << "Data Packet not found in Content Store, sending new Interest Packet";

                if (this->m_pending_interest_table.count(packet.id()) == 0) {
                    std::list<network_node*> l;
                    l.push_back(packet.sender());

                    this->m_pending_interest_table[packet.id()] = l;

                } else {
                    this->m_pending_interest_table[packet.id()].push_back(packet.sender());
                }

                std::list<link*>::iterator link_i;

                for (link_i = this->m_forwarding_nodes.begin(); link_i != this->m_forwarding_nodes.end(); ++link_i) {
                    network::protocol::interest_packet i_p(this, packet.id());
                    (*link_i)->forwarding_node()->lookup(i_p);
                }
            }

            this->m_lookup_requests.pop_front();
        }

        LOG(DEBUG) << "[NETWORK_NODE]" << "Yielding thread";
        std::this_thread::yield();

        LOG(DEBUG) << "[NETWORK_NODE] " << "Verifying incoming Data Packets";
        if (!this->m_response_requests.empty()) {
            network::protocol::data_packet packet = this->m_response_requests.front();

            if (this->m_pending_interest_table.count(packet.id()) == 1) {
                std::list<network_node*> pending = this->m_pending_interest_table[packet.id()];

                std::list<network_node*>::iterator node_i;

                for (node_i = pending.begin(); node_i != pending.end(); ++node_i) {
                    // link has to be bilateral
                    // (*node_i)->forwarding_node()->lookup(i_p);
                }
            }

            this->m_response_requests.pop_front();
        }

        LOG(DEBUG) << "[NETWORK_NODE]" << "Yielding thread";
        std::this_thread::yield();
    }

    LOG(INFO) << "[NETWORK_NODE] " << "Finishing execution";
}

void network::node::network_node::register_forwarding_node(network_node* forwarding_node) {
    LOG(INFO) << "[NETWORK_NODE] " << "Registering new Forwarding node"; // current and forwarding ids?
    this->m_forwarding_nodes.push_back(new link(forwarding_node));
}

void network::node::network_node::lookup(network::protocol::interest_packet packet) {
    LOG(INFO) << "[NETWORK_NODE] " << "Receiving Interest Packet for " << packet.id();
    this->m_lookup_requests.push_back(packet);
}

void network::node::network_node::receive(network::protocol::data_packet packet) {
    LOG(INFO) << "[NETWORK_NODE] " << "Receiving Data Packet for " << packet.id();
    this->m_response_requests.push_back(packet);
}