#ifndef LOOKUP_REQUEST_HPP
#define LOOKUP_REQUEST_HPP

#include "./request.hpp"
#include "./../protocol/interest_packet.hpp"

namespace network {
    namespace node {
        class lookup_request : public request {
        private:
            network::protocol::interest_packet m_packet;

        public:
            lookup_request(network_node* sender, network::protocol::interest_packet packet);
        };
    }
}

#endif