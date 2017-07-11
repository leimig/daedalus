#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

#include <list>
#include <map>
#include <string>

#include "./link.hpp"
#include "../protocol/interest_packet.hpp"
#include "../protocol/data_packet.hpp"

namespace network {
    namespace node {
        class network_node {
        private:
            std::list<network::protocol::interest_packet> m_lookup_requests;
            std::list<network::protocol::data_packet> m_response_requests;

            std::list<link*> m_forwarding_nodes;
            std::map<std::string, std::list<network_node*>> m_pending_interest_table;

        public:
            network_node();
            ~network_node();

            void run();

            void register_forwarding_node(network_node* forwarding_node);
            void lookup(network::protocol::interest_packet packet);
            void receive(network::protocol::data_packet packet);
        };
    }
}

#endif