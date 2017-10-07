#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

#include <chrono>
#include <list>
#include <map>
#include <string>

#include "./network_interface.hpp"

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

        typedef struct pit_entry {
            int id;
            std::chrono::milliseconds timestamp;
        } pit_entry;

        class network_node : public network_interface {
        private:
            int m_id;

            network::node::content_store* m_store;
            network::node::network_interface* m_interface;

            std::map<std::string, std::list<pit_entry>> m_pending_interest_table;

        public:
            network_node(int id, network::node::cache::policy* policy, network::node::network_interface* interface);
            ~network_node();

            virtual int id() { return this->m_id; };

            virtual void handle_lookup(network::node::protocol::interest_packet packet);
            virtual void handle_answer(network::node::protocol::data_packet packet);
        };
    }
}

#endif