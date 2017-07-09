#include <thread>

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
    while (true) {
        if (!this->m_lookup_requests.empty()) {
            network::protocol::interest_packet packet = this->m_lookup_requests.front();

            if (false) { // check content store
                // answer with the packet, if cached
            } else {
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

        if (!this->m_response_requests.empty()) {
            network::protocol::data_packet packet = this->m_response_requests.front();

            if (this->m_pending_interest_table.count(packet.id()) == 1) {
                std::list<network_node*> pending = this->m_pending_interest_table[packet.id];

                std::list<network_node*>::iterator node_i;

                for (node_i = pending.begin(); node_i != pending.end(); ++node_i) {
                    // link has to be bilateral
                    // (*node_i)->forwarding_node()->lookup(i_p);
            }

            this->m_response_requests.pop_front();
        }

        std::this_thread::yield();
    }
}

void network::node::network_node::registerForwardingNode(network_node* forwarding_node) {
    this->m_forwarding_nodes.push_back(new link(forwarding_node));
}

void network::node::network_node::lookup(network::protocol::interest_packet packet) {
    this->m_lookup_requests.push_back(packet);
}

void network::node::network_node::receive(network::protocol::data_packet packet) {
    this->m_response_requests.push_back(packet);
}