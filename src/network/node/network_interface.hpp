#ifndef NETWORK_INTERFACE_HPP
#define NETWORK_INTERFACE_HPP

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

        class network_interface {
        public:
            network_interface() {};
            ~network_interface() {};

            virtual void lookup(protocol::interest_packet packet) = 0;
            virtual void respond(int id, protocol::data_packet packet) = 0;
        };
    }
}

#endif