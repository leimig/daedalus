#ifndef DATA_PACKET_HPP
#define DATA_PACKET_HPP

#include <string>

#include "./packet.hpp"

namespace network {
    namespace protocol {
        class data_packet : public packet {
        private:
            std::string m_id;

        public:
            data_packet(std::string id) {
                this->m_id = id;
            }

            std::string const& id() { return this->m_id; }
        };
    }
}

#endif