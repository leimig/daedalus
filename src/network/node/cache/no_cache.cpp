#include "./no_cache.hpp"
#include "./../protocol/data_packet.hpp"

const std::string network::node::cache::no_cache::id = "NO_CACHE";

network::node::cache::no_cache::no_cache() {
}

network::node::cache::no_cache::~no_cache() {

}

bool network::node::cache::no_cache::has(std::string packet_id) {
    return false;
}

network::node::protocol::data_packet* network::node::cache::no_cache::get(std::string packet_id) {
    return NULL;
}

void network::node::cache::no_cache::put(network::node::protocol::data_packet packet) {

}