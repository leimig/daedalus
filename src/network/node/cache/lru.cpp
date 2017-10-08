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
    auto packet_it = this->m_data.begin();

    for (; packet_it != this->m_data.end(); packet_it++) {
        if (*packet_it == packet_id) {
            break;
        }
    }

    if (packet_it != this->m_data.begin() && packet_it != this->m_data.end()) {
        auto previous_position_it = packet_it;
        previous_position_it--;

        std::swap(*previous_position_it, *packet_it);

        return new network::node::protocol::data_packet_content;
    }

    return NULL;
}

void network::node::cache::lru::put(network::node::protocol::data_packet packet) {
    if (!this->has(packet.packet_id())) {
        if (!this->m_data.empty() && this->m_data.size() >= this->cache_size()) {
            this->m_data.pop_back();
        }

        this->m_data.push_back(packet.packet_id());
    }
}