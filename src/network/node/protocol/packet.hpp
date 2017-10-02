#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>

namespace network {
    namespace node {
        class network_node;

        namespace protocol {
            class packet {
            private:
                int m_originator_id;

            public:
                packet(int originator_id) { this->m_originator_id = originator_id; };
                virtual ~packet();

                virtual std::string const& packet_id() const = 0;
                int originator_id();
            };
        }
    }
}

#endif