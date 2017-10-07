#include "./fifo.hpp"
#include "./../protocol/data_packet.hpp"

const std::string network::node::cache::fifo::id = "FIFO";

network::node::cache::fifo::fifo() {
}

network::node::cache::fifo::~fifo() {
}

bool network::node::cache::fifo::has(std::string packet_id) {
    for (auto it = this->m_data.begin(); it != this->m_data.end(); it++) {
        if (*it == packet_id) {
            return true;
        }
    }

    return false;
}

network::node::protocol::data_packet_content* network::node::cache::fifo::get(std::string packet_id) {
    if (this->has(packet_id)) {
        return new network::node::protocol::data_packet_content;
    }

    return NULL;
}

void network::node::cache::fifo::put(network::node::protocol::data_packet packet) {
    if (!this->m_data.empty()) {
        this->m_data.pop_front();
    }

    this->m_data.push_back(packet.packet_id());
}