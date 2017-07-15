#include "./no_cache.hpp"

network::node::cache::no_cache::no_cache() {
}

network::node::cache::no_cache::~no_cache() {

}

bool network::node::cache::no_cache::has(std::string id) {
    return false;
}

network::node::protocol::data_packet* get(std::string id) {
    return NULL;
}

void network::node::cache::no_cache::put(network::node::protocol::data_packet packet) {

}