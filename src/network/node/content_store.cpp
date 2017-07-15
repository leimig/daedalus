#include "./cache/policy.hpp"
#include "./content_store.hpp"
#include "./protocol/data_packet.hpp"

network::node::content_store::content_store(network::node::cache::policy* policy) {
    this->m_policy = policy;
}

network::node::content_store::~content_store() {
    delete this->m_policy;
}

bool network::node::content_store::has(std::string id) {
    return this->m_policy->has(id);
}

network::node::protocol::data_packet* network::node::content_store::get(std::string id) {
    return this->m_policy->get(id);
}

void network::node::content_store::put(network::node::protocol::data_packet packet) {
    return this->m_policy->put(packet);
}