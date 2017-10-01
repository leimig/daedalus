#ifndef DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <string>
#include "./packet.hpp"

namespace network {
    namespace node {
        namespace protocol {
            class packet;

            class data_packet : public packet {
            private:
                int m_target_id;
                std::string m_packet_id;

            public:
                data_packet(int originator_id, int m_target_id, std::string packet_id) : packet(originator_id) {
                    this->m_target_id = m_target_id;
                    this->m_packet_id = packet_id;
                }

                inline int target_id() { return this->m_target_id; };
                std::string const& packet_id() const { return this->m_packet_id; }
            };
        }
    }
}

#endif