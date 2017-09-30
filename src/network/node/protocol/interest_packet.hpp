#ifndef INTEREST_PACKET_HPP
#define INTEREST_PACKET_HPP

#include <string>
#include "./packet.hpp"

namespace network {
    namespace node {
        namespace protocol {
            class interest_packet : public packet {
            private:
                std::string m_packet_id;

            public:
                interest_packet(int sender_id, std::string packet_id) : packet(sender_id) {
                    this->m_packet_id = packet_id;
                }

                std::string const& packet_id() const { return this->m_packet_id; }
            };
        }
    }
}

#endif