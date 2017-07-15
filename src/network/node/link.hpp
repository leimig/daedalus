#ifndef LINK_HPP
#define LINK_HPP

namespace network {
    namespace node {
        class network_node;

        class link {
        private:
            network_node* m_forwarding_node;

        public:
            link(network_node* forwarding_node);
            ~link();

            network_node* const& forwarding_node() const { return this->m_forwarding_node; }
        };
    }
}

#endif