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
        }

        class network_interface {
        public:
            network_interface() {};
            ~network_interface() {};

            virtual void handle(protocol::packet packet) = 0;
        };
    }
}

#endif