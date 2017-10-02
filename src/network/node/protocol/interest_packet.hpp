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
                interest_packet(int originator_id, std::string packet_id) : packet(originator_id) {
                    this->m_packet_id = packet_id;
                }

                virtual ~interest_packet() {};

                std::string const& packet_id() const { return this->m_packet_id; }
            };
        }
    }
}

#endif