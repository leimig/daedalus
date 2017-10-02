#ifndef NETWORK_INTERFACE_HPP
#define NETWORK_INTERFACE_HPP

#include <chrono>
#include <list>
#include <map>
#include <string>

namespace network {
    namespace node {
        namespace protocol {
            class interest_packet;
            class data_packet;
        }

        class network_interface {
        public:
            network_interface() {};
            virtual ~network_interface() {};

            virtual void handle_lookup(network::node::protocol::interest_packet packet) = 0;
            virtual void handle_answer(network::node::protocol::data_packet packet) = 0;
        };
    }
}

#endif