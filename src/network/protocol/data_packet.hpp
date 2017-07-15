#ifndef DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <string>
#include "./packet.hpp"

namespace network {
    namespace node {
        class network_node;
    }

    namespace protocol {
        class packet;

        class data_packet : public packet {
        private:
            std::string m_id;

        public:
            data_packet(network::node::network_node* sender, std::string id) : packet(sender) {
                this->m_id = id;
            }

            std::string const& id() const { return this->m_id; }
        };
    }
}

#endif