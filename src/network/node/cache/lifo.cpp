#include "./lifo.hpp"
#include "./../protocol/data_packet.hpp"

const std::string network::node::cache::lifo::id = "LIFO";

network::node::cache::lifo::lifo(int cache_size) : policy(cache_size) {
}

network::node::cache::lifo::~lifo() {
}

bool network::node::cache::lifo::has(std::string packet_id) {
    for (auto it = this->m_data.begin(); it != this->m_data.end(); it++) {
        if (*it == packet_id) {
            return true;
        }
    }

    return false;
}

network::node::protocol::data_packet_content* network::node::cache::lifo::get(std::string packet_id) {
    if (this->has(packet_id)) {
        return new network::node::protocol::data_packet_content;
    }

    return NULL;
}

void network::node::cache::lifo::put(network::node::protocol::data_packet packet, data_packet_meta meta) {
    if (!this->has(packet.packet_id())) {
        if (!this->m_data.empty() && this->m_data.size() >= this->cache_size()) {
            this->m_data.pop_back();
        }

        this->m_data.push_back(packet.packet_id());
    }
}