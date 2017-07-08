#include "./lookup_request.hpp"

network::node::lookup_request::lookup_request(network_node* sender, network::protocol::interest_packet packet)
    : request(sender) {

    this->m_packet = packet;
}

network::protocol::packet const& network::node::lookup_request::packet() {
    return this->m_packet;
}