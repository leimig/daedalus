#ifndef RESPONSE_REQUEST_HPP
#define RESPONSE_REQUEST_HPP

#include "./request.hpp"
#include "./../protocol/data_packet.hpp"

namespace network {
    namespace node {
        class response_request : public request {
        private:
            network::protocol::data_packet m_packet;

        public:
            response_request(network_node* sender, network::protocol::data_packet packet);

            virtual network::protocol::packet const& packet() = 0;
        };
    }
}

#endif