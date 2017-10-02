#include "./packet.hpp"

network::node::protocol::packet::~packet() {

}

int network::node::protocol::packet::originator_id() {
    return this->m_originator_id;
}