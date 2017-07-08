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
            interest_packet(std::string id) {
                this->m_id = id;
            }

            std::string const& id() { return this->m_id; }
        };
    }
}

#endif