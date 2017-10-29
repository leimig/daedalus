#ifndef LEAVE_COSTLY_COPY_HPP
#define LEAVE_COSTLY_COPY_HPP

#include <chrono>
#include <string>
#include <list>

#include "./policy.hpp"

namespace network {
    namespace node {
        namespace cache {
            typedef struct leave_costly_copy_entry {
                std::string packet_id;
                std::chrono::milliseconds retrieve_delay;
            } leave_costly_copy_entry;

            class leave_costly_copy : public policy {
            private:
                std::list<leave_costly_copy_entry> m_data;

            public:
                static const std::string id;

                leave_costly_copy(int cache_size);
                ~leave_costly_copy();

                bool has(std::string packet_id);
                network::node::protocol::data_packet_content* get(std::string packet_id);
                void put(network::node::protocol::data_packet packet, data_packet_meta meta);
            };
        }
    }
}

#endif