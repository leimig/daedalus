#ifndef NETWORK_SIMULATOR_HPP
#define NETWORK_SIMULATOR_HPP

#include <list>
#include <thread>
#include <mutex>

#include "./node/network_node.hpp"

namespace network {
    struct network_config {
        std::string topology_name;

        int number_of_threads = 10;
        int number_of_nodes = 50;
        int max_number_of_nodes_in_clusters = 5;
    };

    typedef network_config network_config;

    class network_simulator {
    private:
        network::network_config m_config;
        int m_last_thread_index;
        std::mutex m_next_thread_mutex;

        std::list<std::thread*> m_threads;
        node::network_node **m_nodes;

    public:
        network_simulator(network::network_config config, network::node::network_node **&nodes);
        ~network_simulator();

        void start();
        network::node::network_node* next_node();
    };
}

#endif