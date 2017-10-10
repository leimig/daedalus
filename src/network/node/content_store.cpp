#include "../../results/data_collector.hpp"
#include "./cache/policy.hpp"
#include "./content_store.hpp"
#include "./protocol/data_packet.hpp"

network::node::content_store::content_store(network::node::cache::policy* policy) {
    this->m_policy = policy;
    this->m_tracking_enabled = false;
}

network::node::content_store::~content_store() {
    delete this->m_policy;
}

void network::node::content_store::enable_tracking() {
    this->m_tracking_enabled = true;
}

bool network::node::content_store::has(std::string id) {
    bool contains = this->m_policy->has(id);

    if (this->m_tracking_enabled) {
        if (contains) {
            results::data_collector::instance()->cache_hit();
        } else {
            results::data_collector::instance()->cache_miss();
        }
    }

    return contains;
}

network::node::protocol::data_packet_content* network::node::content_store::get(std::string id) {
    return this->m_policy->get(id);
}

void network::node::content_store::put(network::node::protocol::data_packet packet) {
    return this->m_policy->put(packet);
}