#include "./network_node.hpp"
#include "./lookup_request.hpp"

network::node::network_node::network_node() {

}

network::node::network_node::~network_node() {
    // delete m_requests
    std::list<request*>::iterator request_i;

    for (request_i = this->m_requests.begin(); request_i != this->m_requests.end(); ++request_i)
        delete *request_i;

    // delete m_forwarding_nodes
    std::list<link*>::iterator link_i;

    for (link_i = this->m_forwarding_nodes.begin(); link_i != this->m_forwarding_nodes.end(); ++link_i)
        delete *link_i;
}

void network::node::network_node::registerForwardingNode(network_node* forwarding_node) {
    this->m_forwarding_nodes.push_back(new link(forwarding_node));
}

void network::node::network_node::lookup(network_node* requester, network::protocol::interest_packet packet) {
    this->m_requests.push_back(new lookup_request(requester, packet));
}

void network::node::network_node::receive(network_node* sender, network::protocol::data_packet packet) {

}