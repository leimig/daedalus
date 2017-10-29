#include <iostream>
#include <utility>

#include "./leave_costly_copy.hpp"
#include "./../protocol/data_packet.hpp"

const std::string network::node::cache::leave_costly_copy::id = "LCC";

network::node::cache::leave_costly_copy::leave_costly_copy(int cache_size) : policy(cache_size) {
}

network::node::cache::leave_costly_copy::~leave_costly_copy() {
}

bool network::node::cache::leave_costly_copy::has(std::string packet_id) {
    for (auto it = this->m_data.begin(); it != this->m_data.end(); it++) {
        if (it->packet_id == packet_id) {
            return true;
        }
    }

    return false;
}

network::node::protocol::data_packet_content* network::node::cache::leave_costly_copy::get(std::string packet_id) {
    auto packet_it = this->m_data.begin();

    for (; packet_it != this->m_data.end(); packet_it++) {
        if (packet_it->packet_id == packet_id) {
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

void network::node::cache::leave_costly_copy::put(network::node::protocol::data_packet packet, data_packet_meta meta) {
    leave_costly_copy_entry entry;
    entry.packet_id = packet.packet_id();
    entry.retrieve_delay = meta.delay;

    if (!this->has(packet.packet_id())) {
        if (this->m_data.size() < this->cache_size()) {
            this->m_data.push_back(entry);
        } else {
            if (this->m_data.back().retrieve_delay <= entry.retrieve_delay) {
                this->m_data.pop_back();
                this->m_data.push_back(entry);
            }
        }
    }
}