#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

#include <chrono>
#include <list>
#include <map>
#include <string>

namespace network {
    namespace node {
        class link;
        class content_store;
        class network_node;

        namespace protocol {
            class packet;
            class data_packet;
            class interest_packet;
        }

        typedef struct pit_entry {
            std::chrono::milliseconds timestamp;
            network::node::network_node* node;
        } pit_entry;

        class network_node {
        private:
            std::list<protocol::interest_packet> m_lookup_requests;
            std::list<protocol::data_packet> m_response_requests;

            network::node::content_store* store;
            std::list<link*> m_forwarding_nodes;
            std::map<std::string, std::list<pit_entry>> m_pending_interest_table;

        public:
            network_node();
            ~network_node();

            void run();
            void handle_lookup_request();
            void handle_response_request();

            void register_forwarding_node(network_node* forwarding_node);
            void lookup(protocol::interest_packet packet);
            void receive(protocol::data_packet packet);
        };
    }
}

#endif