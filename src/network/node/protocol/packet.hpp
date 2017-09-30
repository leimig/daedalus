#ifndef PACKET_HPP
#define PACKET_HPP

namespace network {
    namespace node {
        class network_node;

        namespace protocol {
            class packet {
            private:
                int m_sender_id;

            public:
                packet(int sender_id) { this->m_sender_id = sender_id; };
                virtual ~packet() {};

                virtual std::string const& packet_id() const = 0;
                inline int sender_id() { return this->m_sender_id; };
            };
        }
    }
}

#endif