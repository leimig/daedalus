#include <iostream>
#include <utility>

#include "./lfu.hpp"
#include "./../protocol/data_packet.hpp"

const std::string network::node::cache::lfu::id = "LFU";

network::node::cache::lfu::lfu(int cache_size) : policy(cache_size) {
}

network::node::cache::lfu::~lfu() {
}

bool network::node::cache::lfu::has(std::string packet_id) {
    for (auto it = this->m_data.begin(); it != this->m_data.end(); it++) {
        if (it->packet_id == packet_id) {
            return true;
        }
    }

    return false;
}

network::node::protocol::data_packet_content* network::node::cache::lfu::get(std::string packet_id) {
    for (auto entry = this->m_data.begin(); entry != this->m_data.end(); entry++) {
        if (entry->packet_id == packet_id) {
            entry->frequency_count++;
            return new network::node::protocol::data_packet_content;
        }
    }

    return NULL;
}

void network::node::cache::lfu::put(network::node::protocol::data_packet packet, data_packet_meta meta) {
    if (!this->has(packet.packet_id())) {
        if (!this->m_data.empty() && this->m_data.size() >= this->cache_size()) {
            auto it = this->m_data.begin();
            auto it_to_erase = it;
            int least_frequent_counter = 1;

            for (; it != this->m_data.end(); it++) {
                if (it->frequency_count <= least_frequent_counter) {
                    it_to_erase = it;
                }
            }

            this->m_data.erase(it_to_erase);
        }

        lfu_entry entry;
        entry.packet_id = packet.packet_id();

        this->m_data.push_back(entry);
    }
}