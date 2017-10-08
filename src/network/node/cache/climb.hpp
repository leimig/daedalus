#ifndef CLIMB_HPP
#define CLIMB_HPP

#include <string>
#include <list>

#include "./policy.hpp"

namespace network {
    namespace node {
        namespace cache {
            class climb : public policy {
            private:
                std::list<std::string> m_data;

            public:
                static const std::string id;

                climb(int cache_size);
                ~climb();

                bool has(std::string packet_id);
                network::node::protocol::data_packet_content* get(std::string packet_id);
                void put(network::node::protocol::data_packet packet);
            };
        }
    }
}

#endif