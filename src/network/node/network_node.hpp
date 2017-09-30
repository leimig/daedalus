#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

#include <chrono>
#include <list>
#include <map>
#include <string>

namespace network {
    namespace node {
        namespace protocol {
            class packet;
            class data_packet;
            class interest_packet;
        }

        namespace cache {
            class policy;
        }

        class content_store;
        class network_node;
        class network_interface;

        typedef struct pit_entry {
            int id;
            std::chrono::milliseconds timestamp;
        } pit_entry;

        class network_node {
        private:
            int m_id;

            network::node::content_store* m_store;
            network::node::network_interface* m_interface;

            std::map<std::string, std::list<pit_entry>> m_pending_interest_table;

        public:
            network_node(int id, network::node::network_interface* interface, network::node::cache::policy* policy);
            ~network_node();

            void handle_lookup_request();
            void handle_response_request();

            void lookup(protocol::interest_packet packet);
            void receive(protocol::data_packet packet);
        };
    }
}

#endif