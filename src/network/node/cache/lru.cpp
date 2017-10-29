#include <iostream>
#include <utility>

#include "./lru.hpp"
#include "./../protocol/data_packet.hpp"

const std::string network::node::cache::lru::id = "LRU";

network::node::cache::lru::lru(int cache_size) : policy(cache_size) {
}

network::node::cache::lru::~lru() {
}

bool network::node::cache::lru::has(std::string packet_id) {
    for (auto it = this->m_data.begin(); it != this->m_data.end(); it++) {
        if (*it == packet_id) {
            return true;
        }
    }

    return false;
}

network::node::protocol::data_packet_content* network::node::cache::lru::get(std::string packet_id) {
    if (this->has(packet_id)) {
        this->m_data.remove(packet_id);
        this->m_data.push_front(packet_id);
        return new network::node::protocol::data_packet_content;
    }

    return NULL;
}

void network::node::cache::lru::put(network::node::protocol::data_packet packet, data_packet_meta meta) {
    if (!this->has(packet.packet_id())) {
        if (!this->m_data.empty() && this->m_data.size() >= this->cache_size()) {
            this->m_data.pop_back();
        }

        this->m_data.push_back(packet.packet_id());
    }
}