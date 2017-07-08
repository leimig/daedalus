#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

#include <list>
#include <map>
#include <string>

#include "./link.hpp"
#include "./request.hpp"
#include "../protocol/packet.hpp"
#include "../protocol/interest_packet.hpp"
#include "../protocol/data_packet.hpp"

namespace network {
    namespace node {
        class network_node {
        private:
            std::list<request*> m_requests;

            std::list<link*> m_forwarding_nodes;
            std::map<std::string, std::list<network_node*>> m_pending_interest_table;

        public:
            network_node();
            ~network_node();

            void registerForwardingNode(network_node* forwarding_node);
            void lookup(network_node* requester, network::protocol::interest_packet packet);
            void receive(network_node* sender, network::protocol::data_packet packet);
        };
    }
}

#endif