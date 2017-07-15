#ifndef INTEREST_PACKET_HPP
#define INTEREST_PACKET_HPP

#include <string>
#include "./packet.hpp"

namespace network {
    namespace protocol {
        class interest_packet : public packet {
        private:
            std::string m_id;

        public:
            interest_packet(network::node::network_node* sender, std::string id) : packet(sender) {
                this->m_id = id;
            }

            std::string const& id() const { return this->m_id; }
        };
    }
}

#endif