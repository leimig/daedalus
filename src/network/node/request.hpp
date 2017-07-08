#ifndef REQUEST_HPP
#define REQUEST_HPP

namespace network {
    namespace protocol {
        class packet;
    }

    namespace node {
        class network_node;

        class request {
        private:
            network_node* m_sender;

        public:
            request(network_node* sender) { this->m_sender = sender; }

            // A `request` should not delete a network_node,
            // that's why we do not remove sender when a request is deleted.

            inline network_node* sender() { return this->m_sender; }

            virtual network::protocol::packet const& packet() = 0;
        };
    }
}

#endif