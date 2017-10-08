#include "./climb.hpp"
#include "./../protocol/data_packet.hpp"

const std::string network::node::cache::climb::id = "CLIMB";

network::node::cache::climb::climb(int cache_size) : policy(cache_size) {
}

network::node::cache::climb::~climb() {
}

bool network::node::cache::climb::has(std::string packet_id) {
    for (auto it = this->m_data.begin(); it != this->m_data.end(); it++) {
        if (*it == packet_id) {
            return true;
        }
    }

    return false;
}

network::node::protocol::data_packet_content* network::node::cache::climb::get(std::string packet_id) {
    if (this->has(packet_id)) {
        this->m_data.remove(packet_id);
        this->m_data.push_front(packet_id);
        return new network::node::protocol::data_packet_content;
    }

    return NULL;
}

void network::node::cache::climb::put(network::node::protocol::data_packet packet) {
    if (!this->has(packet.packet_id())) {
        if (!this->m_data.empty() && this->m_data.size() >= this->cache_size()) {
            this->m_data.pop_back();
        }

        this->m_data.push_front(packet.packet_id());
    }
}