#ifndef PACKET_HPP
#define PACKET_HPP

namespace network {
    namespace node {
        class network_node;

        namespace protocol {
            class packet {
            private:
                network::node::network_node* m_sender;

            public:
                packet(network::node::network_node* sender) { this->m_sender = sender; }
                virtual ~packet() {}

                virtual std::string const& id() const = 0;
                inline network::node::network_node* sender() { return this->m_sender; }
            };
        }
    }
}

#endif