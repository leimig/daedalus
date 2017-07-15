#include "./cache/policy.hpp"
#include "./content_store.hpp"
#include "./../protocol/data_packet.hpp"

network::node::content_store::content_store(network::node::cache::policy* policy) {
    this->policy = policy;
}

network::node::content_store::~content_store() {
    delete this->policy;
}

bool network::node::content_store::has(std::string id) {
    return this->policy->has(id);
}

network::protocol::data_packet network::node::content_store::get(std::string id) {
    return this->policy->get(id);
}

void network::node::content_store::put(network::protocol::data_packet packet) {
    return this->policy->put(packet);
}